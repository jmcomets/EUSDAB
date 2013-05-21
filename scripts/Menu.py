#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import subprocess
import json
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
        self.preview = character
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
        return len(self.chosen) > 1

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
        self.characters[s].SetSelectColor(sf.Color.Green)
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

_out_file = os.path.join(_entity_dir, 'entities.json')
def save_players(player_dict):
    final_dict = { key : _character_folders[value] \
            for key, value in player_dict.iteritems() }
    json.dump(final_dict, open(_out_file, 'w'))

_exec_name = os.path.join(_root_dir, 'run.sh')
_exec_params = ['entity']
def play_game():
    window = get_window()
    window.Show(False)
    subprocess.call([_exec_name] + _exec_params)
    window.Show(True)

_button_mapping = {
        0 : 'choose',
        1 : 'unchoose',
        7 : 'start'
        }
_dead_zone_limit = 90
if __name__ == '__main__':
    window = get_window()
    players_interface = PlayersInterface()
    bg_sprite = make_sprite('Background.png')
    banner_sprite = make_sprite('Banner.png')
    #load_music('bazar.ogg').Play()
    startup_sound = load_sound('char_selection.ogg')
    startup_sound.Play()
    start_sound = load_sound('press_start.ogg')

    while window.IsOpened():
        _input = window.GetInput()
        event = sf.Event()
        while window.GetEvent(event):
            if event.Type == sf.Event.Closed:
                window.Close()
            elif event.Type == sf.Event.JoyMoved:
                id_ = event.JoyMove.JoystickId
                if event.JoyMove.Axis == sf.Joy.AxisX:
                    val = event.JoyMove.Position
                    if abs(val) >= _dead_zone_limit:
                        delta = val / abs(val)
                        players_interface.MoveSelection(id_, delta)
            elif event.Type == sf.Event.JoyButtonPressed:
                id_ = event.JoyButton.JoystickId
                button = event.JoyButton.Button
                if button in _button_mapping:
                    action = _button_mapping[button]
                    if action == "choose":
                        players_interface.ChooseSelection(id_)
                        if players_interface.CanStart():
                            start_sound.Play()
                    elif action == "unchoose":
                        players_interface.UnChoose(id_)
                    elif action == "start":
                        if players_interface.CanStart():
                            players = players_interface.GetPlayers()
                            save_players(players)
                            play_game()
        window.Clear()
        window.Draw(bg_sprite)
        window.Draw(banner_sprite)
        window.Draw(players_interface)
        window.Display()
