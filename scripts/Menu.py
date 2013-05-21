#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import glob
import subprocess
from PySFML import sf

_root_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))

_window_size = (1280, 720)
_window = None
def get_window():
    global _window
    if _window is None:
        _window = sf.RenderWindow(sf.VideoMode(*_window_size),
                "EUSDAB", sf.Style.Close)
        _window.SetFramerateLimit(30)
    return _window

def get_window_size():
    w = get_window()
    return w.GetWidth(), w.GetHeight()

_assets_dir = os.path.join(_root_dir, 'assets')
_menu_dir = os.path.join(_assets_dir, 'menu')
_base_image_dir = os.path.join(_menu_dir, 'images')
_loaded_images = {}
def load_image(filename):
    global _loaded_images
    if filename not in _loaded_images:
        img = sf.Image()
        fname = os.path.join(_base_image_dir, filename)
        if not img.LoadFromFile(fname):
            raise RuntimeError("Image %s couldn't be loaded" % fname)
        _loaded_images[filename] = img
    return _loaded_images[filename]

_base_musics_dir = os.path.join(_assets_dir, 'audio', 'musics')
_loaded_musics = {}
def load_music(filename):
    global _loaded_musics
    if filename not in _loaded_musics:
        music = sf.Music()
        fname = os.path.join(_base_musics_dir, filename)
        if not music.OpenFromFile(fname):
            raise RuntimeError("Music %s couldn't be loaded" % fname)
        _loaded_musics[filename] = music
    return _loaded_musics[filename]

_base_sounds_dir = os.path.join(_menu_dir, 'sounds')
_loaded_sounds = {}
def load_sound(filename):
    global _loaded_sounds
    if filename not in _loaded_sounds:
        sound_buffer = sf.SoundBuffer()
        fname = os.path.join(_base_sounds_dir, filename)
        if not sound_buffer.LoadFromFile(fname):
            raise RuntimeError("Sound %s couldn't be loaded" % fname)
        _loaded_sounds[filename] = sound_buffer
    return sf.Sound(_loaded_sounds[filename])

def make_sprite(img, center=None):
    if isinstance(img, str):
        img = load_image(img)
    sp = sf.Sprite(img)
    sp.SetCenter(img.GetWidth() / 2., img.GetHeight() / 2.)
    window_size = get_window_size()
    sp.SetPosition(window_size[0] / 2., window_size[1] / 2.)
    if center is not None:
        sp.SetPosition(*center)
    return sp

_name_padding = 20

class CharacterFrame(sf.Drawable):
    def __init__(self, frame_image):
        self.frame_sprite = make_sprite(frame_image)
        w, h = frame_image.GetWidth(), frame_image.GetHeight()
        self.rect = sf.Shape.Rectangle(0, 0, w, h, sf.Color.White)
        self.rect.SetCenter(w / 2., h / 2.)
        self.rect.EnableOutline(False)
        self.rect.EnableFill(False)
        self.rect.SetOutlineWidth(2)
        window_size = get_window_size()
        self.rect.SetPosition(window_size[0] / 2., window_size[1] / 2.)

    def Render(self, target):
        target.Draw(self.frame_sprite)
        target.Draw(self.rect)

    def SetPosition(self, *args):
        self.frame_sprite.SetPosition(*args)
        self.rect.SetPosition(*args)

    def SetSelectColor(self, color):
        self.rect.EnableOutline(True)
        for i in xrange(self.rect.GetNbPoints()):
            self.rect.SetPointOutlineColor(i, color)

    def ResetSelectColor(self):
        self.rect.EnableOutline(False)

class CharacterPreview(sf.Drawable):
    def __init__(self, preview_image, name_image):
        self.preview_sprite = make_sprite(preview_image)
        self.name_sprite = make_sprite(name_image)

    def Render(self, target):
        target.Draw(self.preview_sprite)
        target.Draw(self.name_sprite)

    def SetPreviewPosition(self, *args):
        x, y = args
        self.preview_sprite.SetPosition(x, y)

    def SetNamePosition(self, *args):
        x, y, padding = args
        self.name_sprite.SetPosition(x, y + padding)

class PlayerDisplay(sf.Drawable):
    def __init__(self, none_image, selected_image):
        self.preview = None
        self.none_sprite = make_sprite(none_image)
        self.selected_sprite = make_sprite(selected_image)

    def Render(self, target):
        if self.preview is not None:
            target.Draw(self.selected_sprite)
            target.Draw(self.preview)
        else:
            target.Draw(self.none_sprite)

    def Select(self, character):
        center = self.selected_sprite.GetPosition()
        self.preview = CharacterPreview(character.preview_sprite.GetImage(),
                character.name_sprite.GetImage())
        self.preview.SetPreviewPosition(*center)
        x, y = center
        padding = -self.none_sprite.GetImage().GetHeight() / 2. - _name_padding
        self.preview.SetNamePosition(x, y, padding)

    def UnSelect(self):
        self.preview = None

    def SetPosition(self, *args):
        self.none_sprite.SetPosition(*args)
        self.selected_sprite.SetPosition(*args)

_nbPlayers = 4
_interface_padding = (40, 10)

_color_mapping = [sf.Color.Red, sf.Color.Blue, sf.Color.Yellow, sf.Color.Green]

_characters = {
        'RickHard' : 'rickhard',
        'PedroPanda' : 'panda',
        'Charlie' : 'poney'
        }

_entity_dir = os.path.join(_assets_dir, 'entities')
_character_folders = _characters.values()
_min_to_start = 1

_character_sounds = [load_sound('sound_{}.ogg'.format(x)) \
        for x in _characters]
def play_character_sound(i):
    _character_sounds[i].Play()

class PlayersInterface(sf.Drawable):
    def __init__(self):
        window_size = get_window_size()

        self.previews = []
        self.characters = []
        for i, c in enumerate(_characters):
            preview_img = load_image('preview_{}.png'.format(c))
            name_img = load_image('Name_{}.png'.format(c))
            cd = CharacterPreview(preview_img, name_img)
            self.previews.append(cd)

            frame_image = load_image('cadre_{}.png'.format(c))
            cf = CharacterFrame(frame_image)
            self.characters.append(cf)
            w, h = frame_image.GetWidth(), frame_image.GetHeight()
            nbCharacters = len(_characters)
            padding = 300
            width_padding = (window_size[0]-nbCharacters*w-2*padding)/(nbCharacters-1)
            x = w/2. + (w+width_padding)*i + padding
            y = 170
            cf.SetPosition(x, y)

        self.players = []
        self.chosen = {}
        self.selections = range(_nbPlayers)
        for i in xrange(_nbPlayers):
            none_img = load_image('cadre_nop.png')
            selected_img = load_image('cadre_p{}.png'.format(i + 1))
            pd = PlayerDisplay(none_img, selected_img)
            self.players.append(pd)
            w, h = none_img.GetWidth(), none_img.GetHeight()
            width_padding = (window_size[0]-_nbPlayers*w-2*_interface_padding[0])/(_nbPlayers-1)
            x = w/2. + (w+width_padding)*i + _interface_padding[0]
            y = window_size[1] - h/2. - _interface_padding[1]
            pd.SetPosition(x, y)

        self.start_sprite = make_sprite('Start_Banner.png')
        self.start_sprite.SetPosition(window_size[0]/2., 340)

    def Render(self, target):
        for p in self.players:
            target.Draw(p)
        for c in self.characters:
            target.Draw(c)
        if self.CanStart():
            target.Draw(self.start_sprite)

    def CanStart(self):
        return len(self.chosen) >= _min_to_start

    def GetSelected(self, id_):
        return self.selections[id_]

    def SetSelected(self, id_, s):
        self.selections[id_] = s

    def GetChosen(self, id_):
        return self.chosen[id_]

    def SetChosen(self, id_, s):
        self.chosen[id_] = s

    def SetNotChosen(self, id_):
        if id_ in self.chosen:
            del self.chosen[id_]

    def HasChosen(self, id_):
        return id_ in self.chosen

    def MoveSelection(self, id_, delta):
        if not self.HasChosen(id_):
            s = self.GetSelected(id_)
            self.characters[s].ResetSelectColor()
            s = (s + int(delta)) % len(self.previews)
            self.SetSelected(id_, s)
            self.characters[s].SetSelectColor(_color_mapping[id_])

    def ChooseSelection(self, id_):
        s = self.GetSelected(id_)
        self.characters[s].ResetSelectColor()
        self.players[id_].Select(self.previews[s])
        self.SetChosen(id_, s)
        play_character_sound(s)

    def UnChoose(self, id_):
        if self.HasChosen(id_):
            s = self.GetChosen(id_)
            self.characters[s].SetSelectColor(_color_mapping[id_])
            self.players[id_].UnSelect()
            self.SetNotChosen(id_)

    def GetPlayers(self):
        return self.chosen

    def UnChooseAll(self):
        self.chosen = {}

_exec_name = os.path.join(_root_dir, 'eusdab.sh')
def play_game(map_, player_dict):
    """Run executable : eusdab.sh map j1 ... jn."""
    player_list = []
    for player in xrange(_nbPlayers):
        if player in player_dict:
            character = _character_folders[player_dict[player]]
        else:
            character = 'none'
        player_list.append(character)
    window = get_window()
    call_list = [_exec_name] + [map_] + player_list
    window.Show(False)
    subprocess.call(call_list)
    window.Show(True)

_button_mapping = {
        0 : 'a',
        1 : 'b',
        7 : 'start'
        }

_axis_mapping = {
        sf.Joy.AxisX : 'x',
        sf.Joy.AxisY : 'y'
        }

_dead_zone_limit = 90

class StatesManager:
    def __init__(self):
        self.window = get_window()
        self.states = {}
        self.current = None
        self.InitStates()
        assert_msg = 'Current state should be set in InitStates'
        assert self.current is not None, assert_msg

    def InitStates(self):
        raise NotImplementedError

    def AddState(self, state_id, state):
        if state_id in self.states:
            raise RuntimeError('State %s already defined' % state_id)
        self.states[state_id] = state

    def SwitchState(self, state_id):
        if state_id not in self.states:
            raise RuntimeError('Undefined state %s' % state_id)
        s = self.states[state_id]
        if self.current is not None:
            self.current.Leave()
        self.current = s
        self.current.Enter()

    def SetState(self, state_id):
        if state_id not in self.states:
            raise RuntimeError('Undefined state %s' % state_id)
        self.current = self.states[state_id]

    def Run(self):
        while self.window.IsOpened():
            event = sf.Event()
            while self.window.GetEvent(event):
                if event.Type == sf.Event.Closed:
                    self.window.Close()
                elif event.Type == sf.Event.JoyMoved:
                    id_ = event.JoyMove.JoystickId
                    sfml_axis = event.JoyMove.Axis
                    if sfml_axis in _axis_mapping:
                        axis = _axis_mapping[sfml_axis]
                        position = event.JoyMove.Position
                        if abs(position) >= _dead_zone_limit:
                            self.current.JoystickMoved(id_, axis, position)
                elif event.Type == sf.Event.JoyButtonPressed:
                    id_ = event.JoyButton.JoystickId
                    button = event.JoyButton.Button
                    if button in _button_mapping:
                        action = _button_mapping[button]
                        self.current.JoystickButtonPressed(id_, action)
                elif event.Type == sf.Event.JoyButtonReleased:
                    id_ = event.JoyButton.JoystickId
                    button = event.JoyButton.Button
                    if button in _button_mapping:
                        action = _button_mapping[button]
                        self.current.JoystickButtonReleased(id_, button)
            self.current.Update()
            if not self.current.IsAlive():
                self.SwitchState(self.current.GetNextState())
            self.window.Clear()
            self.current.RenderTo(self.window)
            self.window.Display()

class MenuState:
    def __init__(self):
        self.alive = True
        self.next_state = None

    def SetAlive(self, alive):
        self.alive = bool(alive)

    def IsAlive(self):
        return self.alive

    def GetNextState(self):
        return self.next_state

    def SetNextState(self, state_id):
        self.next_state = state_id

    def Enter(self): pass
    def Update(self): pass
    def Leave(self): pass
    def RenderTo(self, target): pass
    def JoystickMoved(self, id_, axis, position): pass
    def JoystickButtonPressed(self, id_, button): pass
    def JoystickButtonReleased(self, id_, button): pass

class Startup(MenuState):
    def __init__(self):
        MenuState.__init__(self)
        self.bg_sprite = make_sprite('StartupBackground.png')

    def Enter(self):
        # TODO drop background images
        pass

    def RenderTo(self, target):
        target.Draw(self.bg_sprite)

class CharacterSelection(MenuState):
    def __init__(self):
        MenuState.__init__(self)
        self.players_interface = PlayersInterface()
        self.bg_sprite = make_sprite('Background.png')
        self.banner_sprite = make_sprite('Banner.png')
        self.startup_sound = load_sound('char_selection.ogg')
        self.startup_sound.Play()
        self.start_sound = load_sound('press_start.ogg')

    def Enter(self):
        self.players_interface.UnChooseAll()

    def JoystickMoved(self, id_, axis, position):
        if axis == 'x':
            delta = position / abs(position)
            self.players_interface.MoveSelection(id_, delta)

    def JoystickButtonPressed(self, id_, button):
        if button == 'a':
            self.players_interface.ChooseSelection(id_)
            if self.players_interface.CanStart():
                self.start_sound.Play()
        elif button == 'b':
            self.players_interface.UnChoose(id_)
        elif button == 'start':
            if self.players_interface.CanStart():
                players = self.players_interface.GetPlayers()
                play_game('map_bazar', players)

    def RenderTo(self, target):
        target.Draw(self.bg_sprite)
        target.Draw(self.banner_sprite)
        target.Draw(self.players_interface)

_map_dir = os.path.join(_base_image_dir, 'maps')
class MapSelection(MenuState):
    def __init__(self):
        map_glob = os.path.join(_map_dir, '*.png')
        self.maps = [make_sprite(x) for x in glob.glob(map_glob)]
        # TODO set map positions

    def RenderTo(self, target):
        for m in self.maps:
            target.Draw(m)

class MenuStatesManager(StatesManager):
    def InitStates(self):
        #self.AddState('startup', Startup())
        #self.AddState('maps', MapSelection())
        self.AddState('characters', CharacterSelection())
        self.SetState('characters')

if __name__ == '__main__':
    msm = MenuStatesManager()
    msm.Run()
