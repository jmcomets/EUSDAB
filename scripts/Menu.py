#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import glob
import random
import subprocess
import threading
from PySFML import sf

_root_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))

_assets_dir = os.path.join(_root_dir, 'assets')
_menu_dir = os.path.join(_assets_dir, 'menu')

# Loading images
_base_image_dir = os.path.join(_menu_dir, 'images')
_loaded_images = {}
def load_image(filename, basedir=_base_image_dir):
    global _loaded_images
    fname = os.path.join(basedir, filename)
    if filename not in _loaded_images:
        img = sf.Image()
        if not img.LoadFromFile(fname):
            raise RuntimeError("Image %s couldn't be loaded" % fname)
        _loaded_images[fname] = img
    return _loaded_images[fname]

# Global access to window
_window_size = (1280, 720)
_icon_image = 'icon.png'
_window = None
def get_window():
    global _window
    if _window is None:
        _window = sf.RenderWindow(sf.VideoMode(*_window_size),
                "EUSDAB", sf.Style.Close)
        _window.SetFramerateLimit(60)
        icon_image = load_image(_icon_image, _assets_dir)
        _window.SetIcon(icon_image.GetWidth(), icon_image.GetHeight(),
                icon_image.GetPixels())
    return _window

def get_window_size():
    w = get_window()
    return w.GetWidth(), w.GetHeight()

# Loading musics
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

# Loading sounds
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

    def SetPosition(self, *args):
        self.none_sprite.SetPosition(*args)
        self.selected_sprite.SetPosition(*args)

_nbPlayers = 4
_interface_padding = (40, 10)

_color_mapping = [sf.Color.Red, sf.Color.Blue, sf.Color.Yellow, sf.Color.Green]

_characters = {
        'RickHard'   : 'rickhard',
        'PedroPanda' : 'panda',
        'Charlie'    : 'poney',
        'Botato'     : 'botato'
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

    def MoveSelection(self, id_, delta):
        if id_ not in self.chosen:
            s = self.selections[id_]
            self.characters[s].ResetSelectColor()
            s = (s + int(delta)) % len(self.previews)
            self.selections[id_] = s
            self.characters[s].SetSelectColor(_color_mapping[id_])

    def ChooseSelection(self, id_):
        s = self.selections[id_]
        self.characters[s].ResetSelectColor()
        self.players[id_].Select(self.previews[s])
        self.chosen[id_] = s
        play_character_sound(s)

    def UnChoose(self, id_):
        if id_ in self.chosen:
            s = self.chosen[id_]
            self.characters[s].SetSelectColor(_color_mapping[id_])
            self.players[id_].preview = None
            del self.chosen[id_]

    def UnChooseAll(self):
        for id_, s in self.chosen.iteritems():
            s = self.chosen[id_]
            self.characters[s].SetSelectColor(_color_mapping[id_])
            self.players[id_].preview = None
        self.chosen = {}

_player_interface = None
def get_player_interface():
    global _player_interface
    if _player_interface is None:
        _player_interface = PlayersInterface()
    return _player_interface

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
    if len(sys.argv) > 1:
        call_list += ["psyche"]
    print call_list
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
        self.current.alive = True

    def SetState(self, state_id):
        if state_id not in self.states:
            raise RuntimeError('Undefined state %s' % state_id)
        self.current = self.states[state_id]
        self.current.Enter()

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
            if not self.current.alive:
                self.SwitchState(self.current.next_state)
            self.window.Clear()
            self.current.RenderTo(self.window)
            self.window.Display()

class MenuState:
    def __init__(self):
        self.alive = True
        self.next_state = None

    def SwitchState(self, state_id):
        self.alive = False
        self.next_state = state_id

    def Enter(self): pass
    def Update(self): pass
    def Leave(self): pass
    def RenderTo(self, target): pass
    def JoystickMoved(self, id_, axis, position): pass
    def JoystickButtonPressed(self, id_, button): pass
    def JoystickButtonReleased(self, id_, button): pass

_maps_id = 'maps'
_startup_id = 'startup'
_characters_id = 'characters'

_startup_dir = os.path.join(_base_image_dir, 'startup')
_fall_speed = 40
_stack_overflow = 40
_start_padding = 20
_start_extra = -5000
class Startup(MenuState):
    def __init__(self):
        MenuState.__init__(self)
        self.bg_sprite = make_sprite('Background.png')
        startup_glob = os.path.join(_startup_dir, '*.png')
        sprite_list = sorted(glob.glob(startup_glob), reverse=True)
        self.startup_sprites = [make_sprite(x) for x in sprite_list]
        for i, s in enumerate(self.startup_sprites):
            x, _ = s.GetPosition()
            h = s.GetImage().GetHeight()
            if i == 0:
                s.SetPosition(x, _start_extra - h)
            else:
                s.SetPosition(x, -h)
        self.moving_index = 0
        self.max_y = get_window_size()[1] - _start_padding
        self.eusdab_sound = load_sound('EUSDAB.ogg')

    def Enter(self):
        self.eusdab_sound.Play()

    def Leave(self):
        self.eusdab_sound.Stop()

    def Update(self):
        if self.moving_index < len(self.startup_sprites):
            current = self.startup_sprites[self.moving_index]
            x, y = current.GetPosition()
            h = current.GetImage().GetHeight()
            real_max_y = self.max_y - h/2. + _stack_overflow
            y = min(y + _fall_speed, real_max_y)
            current.SetPosition(x, y)
            if y == real_max_y:
                self.moving_index += 1
                self.max_y = real_max_y - h/2.

    def RenderTo(self, target):
        target.Draw(self.bg_sprite)
        for sp in sorted(self.startup_sprites):
            target.Draw(sp)

    def JoystickButtonPressed(self, id_, button):
        if button == 'start':
            self.SwitchState(_characters_id)

class CharacterSelection(MenuState):
    def __init__(self):
        MenuState.__init__(self)
        self.players_interface = get_player_interface()
        self.bg_sprite = make_sprite('Background.png')
        self.banner_sprite = make_sprite('Banner.png')
        self.startup_sound = load_sound('char_selection.ogg')

    def Enter(self):
        self.players_interface.UnChooseAll()
        self.startup_sound.Play()

    def JoystickMoved(self, id_, axis, position):
        if axis == 'x':
            delta = position / abs(position)
            self.players_interface.MoveSelection(id_, delta)

    def JoystickButtonPressed(self, id_, button):
        if button == 'a':
            self.players_interface.ChooseSelection(id_)
        elif button == 'b':
            self.players_interface.UnChoose(id_)
        elif button == 'start':
            if self.players_interface.CanStart():
                players = self.players_interface.chosen
                self.SwitchState(_maps_id)

    def RenderTo(self, target):
        target.Draw(self.bg_sprite)
        target.Draw(self.banner_sprite)
        target.Draw(self.players_interface)

_maps = ['map_bazar', 'map_bar']
_map_dir = os.path.join(_base_image_dir, 'maps')
_map_images = [load_image('{}.png'.format(x), _map_dir) \
        for x in _maps]
_map_padding = 50
class MapSelection(MenuState):
    def __init__(self):
        MenuState.__init__(self)
        self.maps = [make_sprite(x) for x in _map_images]
        window_size = get_window_size()
        N = len(self.maps)
        if N > 1:
            for i, m in enumerate(self.maps):
                img = m.GetImage()
                w, h = img.GetWidth(), img.GetHeight()
                x, y = m.GetPosition()
                p = (window_size[0] - 2*_map_padding - N*w) / (N - 1)
                x = _map_padding + w / 2. + i*w + (i - 1)*p
                m.SetPosition(x, y)

        self.bg_sprite = make_sprite('Background.png')

        w = max(m.GetImage().GetWidth() for m in self.maps)
        h = max(m.GetImage().GetHeight() for m in self.maps)
        self.rect = sf.Shape.Rectangle(0, 0, w, h, sf.Color.White)
        self.rect.SetCenter(w / 2., h / 2.)
        self.rect.EnableOutline(False)
        self.rect.EnableFill(False)
        self.rect.SetOutlineWidth(2)
        for i in xrange(self.rect.GetNbPoints()):
            self.rect.SetPointOutlineColor(i, sf.Color.Yellow)

        self.selected = None

    def RenderTo(self, target):
        target.Draw(self.bg_sprite)
        for i, m in enumerate(self.maps):
            target.Draw(m)
            if self.selected == i:
                self.rect.SetPosition(*m.GetPosition())
                target.Draw(self.rect)

    def JoystickMoved(self, id_, axis, position):
        delta = position / abs(position)
        if axis == 'x':
            if self.selected is None:
                self.rect.EnableOutline(True)
                self.selected = 0
            else:
                self.selected = (self.selected + 1) % len(self.maps)
        elif axis == 'y': pass # TODO

    def JoystickButtonPressed(self, id_, button):
        if button == 'start' or button == 'a':
            if self.selected is None:
                chosen = random.choice(range(len(_maps)))
            else:
                chosen = self.selected
            players = get_player_interface().chosen
            play_game(_maps[chosen], players)
            self.SwitchState(_characters_id)
        elif button == 'b':
            self.SwitchState(_characters_id)

class MenuStatesManager(StatesManager):
    def InitStates(self):
        self.AddState(_startup_id, Startup())
        self.AddState(_maps_id, MapSelection())
        self.AddState(_characters_id, CharacterSelection())
        self.SetState(_startup_id)
        #self.SetState(_maps_id)

if __name__ == '__main__':
    msm = MenuStatesManager()
    msm.Run()
