#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
from PySFML import sf

_window_size = (1280, 720)
_window = None
def get_window():
    global _window
    if _window is None:
        _window = sf.RenderWindow(sf.VideoMode(*_window_size),
                "EUSDAB", sf.Style.Close)
    return _window

def get_window_size():
    w = get_window()
    return w.GetWidth(), w.GetHeight()

_basedir = os.path.join('assets', 'menu')
_loaded_images = {}
def load_image(filename):
    global _loaded_images
    if filename not in _loaded_images:
        img = sf.Image()
        fname = os.path.join(_basedir, filename)
        if not img.LoadFromFile(fname):
            raise RuntimeError("Image %s couldn't be loaded" % fname)
        _loaded_images[filename] = img
    return _loaded_images[filename]

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
        self.rect.EnableOutline(True)
        self.rect.EnableFill(False)
        self.rect.SetOutlineWidth(1)
        window_size = get_window_size()
        self.rect.SetPosition(window_size[0] / 2., window_size[1] / 2.)

    def Render(self, target):
        target.Draw(self.frame_sprite)
        target.Draw(self.rect)

    def SetPosition(self, *args):
        self.frame_sprite.SetPosition(*args)
        self.rect.SetPosition(*args)

    def SetSelectColor(self, color):
        assert isinstance(color, sf.Color)
        for i in xrange(self.rect.GetNbPoints()):
            self.rect.SetPointOutlineColor(i, color)

class CharacterPreview(sf.Drawable):
    def __init__(self, preview_image, name_image):
        assert isinstance(preview_image, sf.Image)
        assert isinstance(name_image, sf.Image)
        self.preview_sprite = make_sprite(preview_image)
        self.name_sprite = make_sprite(name_image)

    def Render(self, target):
        target.Draw(self.preview_sprite)
        target.Draw(self.name_sprite)

    def SetPosition(self, *args):
        x, y = args
        self.preview_sprite.SetPosition(x, y)
        padding = -self.preview_sprite.GetImage().GetHeight() / 2. - _name_padding
        self.name_sprite.SetPosition(x, y + padding)

class PlayerDisplay(sf.Drawable):
    def __init__(self, none_image, selected_image):
        assert isinstance(none_image, sf.Image)
        assert isinstance(selected_image, sf.Image)
        self.preview = None
        self.none_sprite = make_sprite(none_image)
        self.selected_sprite = make_sprite(selected_image)

    def Render(self, target):
        if self.preview is not None:
            target.Draw(self.preview)
            target.Draw(self.selected_sprite)
        else:
            target.Draw(self.none_sprite)

    def Select(self, character):
        assert isinstance(character, CharacterPreview)
        center = self.selected_sprite.GetPosition()
        self.preview = character
        self.preview.SetPosition(*center)

    def UnSelect(self):
        self.preview = None

    def SetPosition(self, *args):
        self.none_sprite.SetPosition(*args)
        self.selected_sprite.SetPosition(*args)

_nbPlayers = 4
_interface_padding = (40, 10)

_color_mapping = [sf.Color.Red, sf.Color.Blue, sf.Color.Yellow, sf.Color.Green]

_characters = ["RickHard", "PedroPanda", "Charlie"]

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
            y = 200
            cf.SetPosition(x, y)

        self.players = []
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
            pd.Select(self.previews[i % len(self.previews)])

    def Render(self, target):
        for p in self.players:
            target.Draw(p)
        for c in self.previews:
            target.Draw(c)
        for c in self.characters:
            target.Draw(c)

if __name__ == '__main__':
    window = get_window()
    players_interface = PlayersInterface()
    bg_sprite = make_sprite('Background.png')
    banner_sprite = make_sprite('Banner.png')
    start_sprite = make_sprite('Start_Banner.png')

    while window.IsOpened():
        _input = window.GetInput()
        event = sf.Event()
        while window.GetEvent(event):
            if event.Type == sf.Event.Closed:
                window.Close()
            elif event.Type == sf.Event.JoyMoved:
                print 'joymoved'
        window.Clear()
        window.Draw(bg_sprite)
        window.Draw(banner_sprite)
        window.Draw(players_interface)
        window.Draw(start_sprite)
        window.Display()
