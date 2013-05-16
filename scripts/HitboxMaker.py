#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import argparse
import json
from PySFML import sf

# Hitbox classes

class Point:
    """Point class handling basic geometry
    operations and unpacking to (x, y) iterable.
    """
    def __init__(self, x=0, y=0):
        self.x, self.y = map(float, (x, y))

    def copy(self):
        x, y = self.x, self.y
        return Point(x, y)

    def __iter__(self):
        """Allow unpacking / iteration on (x, y)."""
        return iter((self.x, self.y))

    def __getitem__(self, index):
        """Allow array access on (x, y)."""
        return (self.x, self.y)[index]

    def __repr__(self):
        return repr((self.x, self.y))

class Semantics:
    """Mock class holding the different hitbox semantics."""

    # Different semantic constants
    FOOT     = 'foot'
    GRAB     = 'grab'
    ATTACK   = 'attack'
    DEFENSE  = 'defense'
    GRABABLE = 'grabable'

    # Set containing the different semantic constants
    SET = (FOOT, GRAB, ATTACK, DEFENSE, GRABABLE)

class Hitbox:
    """Hitbox class handling hitbox semantics and basic
    geometry operations.
    """
    def __init__(self, center, width, height, semantic):
        self.center = Point(*center)
        self.width, self.height = float(width), float(height)
        if self.width <= 0:
            raise RuntimeError('Hitbox width must be strictly positive')
        if self.height <= 0:
            raise RuntimeError('Hitbox height must be strictly positive')
        if semantic not in Semantics.SET:
            raise RuntimeError('Hitbox semantic must be a valid semantic')
        self.semantic = semantic

    def __contains__(self, arg):
        if isinstance(arg, Point):
            return self.contains_point(arg)
        else:
            p = Point(*arg)
            return p in self

    def __repr__(self):
        return repr({
            'center': repr(self.center),
            'width': repr(self.width),
            'height': repr(self.height),
            'semantic': repr(self.semantic)
            })

    def top_left(self):
        half_width = self.width / 2.
        half_height = self.height / 2.
        return self.center[0] - half_width, self.center[1] - half_height

    def bottom_right(self):
        half_width = self.width / 2.
        half_height = self.height / 2.
        return self.center[0] + half_width, self.center[1] + half_height

    def dimensions(self):
        return self.width, self.height

    def contains_point(self, p):
        assert isinstance(p, Point)
        x, y = p.x, p.y
        minX, minY = self.top_left()
        maxX, maxY = self.bottom_right()
        return x >= minX and x <= maxX \
                and y >= minY and y <= maxY

    def copy(self):
        center = self.center.copy()
        width, height = self.width, self.height
        semantic = self.semantic
        return Hitbox(center, width, height, semantic)

class SemanticColors:
    """Mock class holding the mapping from semantic to SFML color."""
    COLORS = {
            Semantics.FOOT     : sf.Color.Magenta,
            Semantics.GRAB     : sf.Color.Yellow,
            Semantics.ATTACK   : sf.Color.Red,
            Semantics.DEFENSE  : sf.Color.Green,
            Semantics.GRABABLE : sf.Color.Blue
            }

class DrawableHitbox(sf.Drawable):
    """Basic graphic representation of a Hitbox."""
    def __init__(self, hitbox):
        assert isinstance(hitbox, Hitbox), 'Must be of type Hitbox'
        self.hitbox = hitbox
        self.selected = False
        left, top = hitbox.top_left()
        width, height = hitbox.dimensions()
        fill_color = sf.Color.Black
        self.drawable = sfml_make_rect_from_def(left, top,
                width, height, fill_color)
        self.drawable.EnableFill(False)
        self.set_semantic(self.hitbox.semantic)

    def Render(self, target):
        if self.selected:
            self.drawable.SetOutlineWidth(2)
        else:
            self.drawable.SetOutlineWidth(1)
        target.Draw(self.drawable)

    def set_semantic(self, semantic):
        assert semantic in SemanticColors.COLORS, \
                'No mapping defined from semantic to actual SFML color'
        self.color = SemanticColors.COLORS[semantic]
        self.hitbox.semantic = semantic
        self.drawable = sfml_set_rect_outline_color(self.drawable, self.color)

    def copy(self):
        hitbox = self.hitbox.copy()
        return DrawableHitbox(hitbox)

class DrawableHitboxList(sf.Drawable):
    def __init__(self):
        self.drawables = []

    def Render(self, target):
        """SFML Drawable boilerplate, delegate to concrete drawables."""
        for d in self.drawables:
            target.Draw(d)

    def append(self, d):
        """Append a hitbox, checking assertions."""
        assert isinstance(d, DrawableHitbox), 'Must be of type DrawableHitbox'
        self.drawables.append(d)

    def remove(self, d):
        """Remove a hitbox, checking assertions."""
        assert isinstance(d, DrawableHitbox), 'Must be of type DrawableHitbox'
        self.drawables.remove(d)

    def select_all(self, semantic=None):
        """Select all hitboxes by semantic (default = all) and return them."""
        assert semantic is None or semantic is Semantics.SET, \
                'Must be a valid semantic'
        s = []
        for d in self.drawables:
            if semantic is None or d.hitbox.semantic == semantic:
                d.selected = True
                s.append(d)
        return s

    def get_selected(self, semantic=None):
        """Copy all selected hitboxes by semantic (default = all)
        and return them.
        """
        assert semantic is None or semantic is Semantics.SET, \
                'Must be a valid semantic'
        s = []
        for d in self.drawables:
            if d.selected:
                if semantic is None or d.hitbox.semantic == semantic:
                    s.append(d)
        return s

    def copy_selected(self, semantic=None):
        """Copy all selected hitboxes by semantic (default = all)
        and return them.
        """
        assert semantic is None or semantic is Semantics.SET, \
                'Must be a valid semantic'
        s = []
        for d in self.drawables:
            if d.selected:
                if semantic is None or d.hitbox.semantic == semantic:
                    new_d = d.copy()
                    s.append(new_d)
        return s

    def clear_selection(self, semantic=None):
        """Unselect all hitboxes by semantic (default = all) and return those
        who are still selected.
        """
        assert semantic is None or semantic is Semantics.SET, \
                'Must be a valid semantic'
        s = []
        for d in self.drawables:
            if semantic is None or d.hitbox.semantic == semantic:
                d.selected = False
            else:
                s.append(d)
        return s

    def toggle_select(self, x, y):
        """Toggle selection of hitboxes, setting their `selected`
        flag to True. Return a list of selected hitboxes."""
        s = []
        toggled = False
        for d in reversed(self.drawables):
            if (x, y) in d.hitbox and not toggled:
                d.selected = not d.selected
                toggled = True
            if d.selected:
                s.append(d)
        return s

    def __iter__(self):
        return iter(self.drawables)

    def __len__(self):
        return len(self.drawables)

# Hitbox helpers

def make_hitbox(start, end, semantic):
    """Helper function returning an Hitbox from any two
    opposite corners of the desired rectangle.
    Returns None if Hitbox creation failed.
    """
    zipped = zip(start, end)
    top_left = tuple(map(float, map(min, zipped)))
    dimensions = width, height = map(lambda p: abs(p[0] - p[1]), zipped)
    center = map(sum, zip(top_left, map(lambda x: x / 2., dimensions)))
    if width > 0 and height > 0:
        hitbox = Hitbox(center, width, height, semantic)
        return hitbox
    else:
        return None

# SFML helpers / hacks

def sfml_make_rect_from_def(left, top, width, height, color=sf.Color.White,
        outline_width=0., outline_color=sf.Color.Black):
    """Helper function returning an SFML Rectangle built with it's
    color and outline width / color.
    """
    rect = sf.Shape.Rectangle(0, 0, width, height, color,
            outline_width, outline_color)
    rect.SetPosition(left, top)
    return rect

def sfml_make_rect_from_corners(start, end):
    """Helper function returning an SFML Rectangle from any two
    opposite corners of the desired rectangle.
    """
    zipped = zip(start, end)
    left, top = map(float, map(min, zipped))
    width, height = map(lambda p: abs(p[0] - p[1]), zipped)
    rect = sfml_make_rect_from_def(left, top, width, height)
    return rect

def sfml_set_rect_outline_color(shape, color):
    """Hack function resolving SFML 1.6's missing shape system."""
    for i in xrange(shape.GetNbPoints()):
        shape.SetPointOutlineColor(i, color)
    return shape

# Generic drawable animation

class DrawableAnimation(sf.Drawable):
    """Drawable Animation, allowing advancing by a default/custom
    delta, generic rendering (provided a function to get the drawable
    element in the "frames" element.
    """
    def __init__(self, frames, fpi=3, get=lambda x: x):
        """Construct from list of frames and functor"""
        try:
            frame_it = iter(frames)
        except TypeError:
            raise AssertionError('animation frames must be iterable')
        assert len(frames) > 0, 'animation frames cannot be empty'
        self.frames = frames
        assert callable(get), 'get argument should be callable'
        self.get = get
        self.index = 0
        self.fpi = fpi

    def Render(self, target):
        """sf.Drawable boilerplate for rendering."""
        target.Draw(self.get(self.current()))

    def advance(self, delta=1):
        """Advance the animation (default delta is 1)."""
        self.index = (self.index + delta) % len(self.frames)

    def current(self):
        """Return current frame."""
        return self.frames[self.index]

    def __iter__(self):
        return iter(self.frames)

    def __len__(self):
        return len(self.frames)

# Actual drawable frame

class DrawableFrame(sf.Drawable):
    """Drawable frame encapsulating its hitboxes."""
    def __init__(self, filename, animation_name, image_folder, x=0, y=0):
        # file name / animation_name
        self.filename = filename.rstrip(os.path.sep)
        self.animation_name = animation_name

        # background image
        self.image = sf.Image()
        fullfilename = os.path.join(image_folder, animation_name, filename)
        if not self.image.LoadFromFile(fullfilename):
            raise RuntimeError("Image '%s' couldn't be loaded" % filename)
        width, height = self.image.GetWidth(), self.image.GetHeight()

        # background sprite
        self.sprite = sf.Sprite(self.image)
        self.sprite.SetCenter(width / 2., height / 2.)
        self.sprite.SetPosition(x, y)

        # information string
        string_repr = os.path.join(self.animation_name, self.filename)
        self.string = sf.String(string_repr)
        self.string.SetCenter(self.string.GetRect().GetWidth() / 2., 0.)
        self.string.SetPosition(x, y + height / 2.)

        # sprite outline rect
        self.rect = sfml_make_rect_from_def(x - width / 2.,
                y - height / 2., width, height)
        self.rect.EnableOutline(True)
        self.rect.EnableFill(False)
        self.rect.SetOutlineWidth(1)
        self.rect = sfml_set_rect_outline_color(self.rect, sf.Color.White)

        # offset for hitboxes
        self.offsetX, self.offsetY = x, y

        # hitboxes
        self.drawable_list = DrawableHitboxList()

    def Render(self, target):
        target.Draw(self.string)
        target.Draw(self.sprite)
        target.Draw(self.rect)
        target.Draw(self.drawable_list)

    def get_hitboxes(self):
        """Get the actual hitbox list for a frame."""
        #return [d.hitbox for d in self.drawable_list]
        hitboxes = []
        for d in self.drawable_list:
            hb = d.hitbox
            hb.center.x += -self.offsetX
            hb.center.y += -self.offsetY
            hitboxes.append(hb)
        return hitboxes

# Saving / Loading hitboxes

def load_hitboxes(animation_name, image_folder, json_file, x, y):
    """Save the animation to JSON."""
    dct = json.load(json_file)
    image_frames = []
    fpi = dct['fpi']
    frames = dct['frames']
    for filename, hitbox_list in sorted(frames.items(), key=lambda x: x[0]):
        try:
            df = DrawableFrame(filename, animation_name, image_folder, x, y)
            for hb in hitbox_list:
                center_dict = hb['center']
                center = center_dict['x'] + x, center_dict['y'] + y
                width, height = hb['width'], hb['height']
                semantic = hb['semantic']
                hitbox = Hitbox(center, width, height, semantic)
                df.drawable_list.append(DrawableHitbox(hitbox))
            image_frames.append(df)
        except RuntimeError: pass
    if len(image_frames) == 0:
        raise RuntimeError('Animation not found in "%s"' % image_folder)
    return DrawableAnimation(image_frames, fpi)

def save_hitboxes(animation, json_file):
    """Save the animation to JSON."""
    assert isinstance(animation, DrawableAnimation), 'Must be animation'
    filename_to_hitboxes = {}
    for frame in animation:
        assert isinstance(frame, DrawableFrame), 'Should be DrawableFrame'
        filename = frame.filename
        animation_name = frame.animation_name
        hitboxes = frame.get_hitboxes()
        filename_to_hitboxes[filename] = hitboxes
    json_data = {'fpi': animation.fpi, 'frames': filename_to_hitboxes}
    def custom_encoder(o):
        if isinstance(o, (Point, Hitbox)):
            return o.__dict__
        raise TypeError('%s is not JSON serializable' % repr(o))
    json_file = open(json_file.name, 'w')
    json_file.write(json.dumps(json_data,
        default=custom_encoder, sort_keys=True))

# Semantic GUI for a nicer interface

class SemanticGUI(sf.Drawable):

    # key mapping to switch current semantic
    MAPPING = {
            sf.Key.A : Semantics.ATTACK,
            sf.Key.Z : Semantics.DEFENSE,
            sf.Key.E : Semantics.FOOT,
            sf.Key.R : Semantics.GRABABLE,
            sf.Key.T : Semantics.GRAB,
            sf.Key.Y : None
            }

    def __init__(self, semantic=None):
        self.semantic = semantic

    def Render(self, target):
        pass

# Main program

def main(json_file, animation_folder, image_folder):
    # IO preparations
    animation_folder_full = os.path.join(image_folder, animation_folder)
    if not os.path.exists(animation_folder_full):
        msg = '"%s" folder does not exist' % animation_folder_full
        raise RuntimeError(msg)
    image_files = os.listdir(animation_folder_full)

    # main window
    window = sf.RenderWindow(sf.VideoMode.GetMode(0), \
            'HitboxMaker', sf.Style.Close | sf.Style.Resize)
    window_center = window.GetWidth() / 2., window.GetHeight() / 2.

    # mouse start click
    start = None

    # current hitbox semantic
    semantic = None

    # currently selected hitboxes
    selected = []

    # currently copied hitboxes
    copied = []

    # hitbox semantic key mapping
    semantic_mapping = {
            sf.Key.A : Semantics.ATTACK,
            sf.Key.Z : Semantics.DEFENSE,
            sf.Key.E : Semantics.FOOT,
            sf.Key.R : Semantics.GRABABLE,
            sf.Key.T : Semantics.GRAB,
            sf.Key.Y : None
            }

    # lambdas for more explicit calls
    is_image_filename = lambda x: x in ('png', 'jpeg', 'jpg', 'bmp')
    get_clean_extension = lambda x: os.path.splitext(x)[1][1:].lower()
    is_readable = lambda x: x.mode[0] == 'r'

    # image list
    image_frames = []
    if is_readable(json_file):
        animation = load_hitboxes(animation_folder, image_folder,
                json_file, *window_center)
    else:
        for x in image_files:
            if is_image_filename(get_clean_extension(x)):
                df = DrawableFrame(x, animation_folder, image_folder, \
                        *window_center)
                image_frames.append(df)
        if len(image_frames) == 0:
            msg = 'No images found in "%s"' % animation_folder_full
            raise RuntimeError(msg)
        image_frames = sorted(image_frames, key=lambda x: x.filename)
        animation = DrawableAnimation(image_frames)

    # camera setup
    camera = sf.View()
    camera.SetCenter(*window_center)
    camera.SetHalfSize(*window_center)

    # helper for mouse querying
    real_mouse_position = lambda x, y: window.ConvertCoords(x, y)

    # helper for zooming
    def zoomBy(delta):
        assert delta != 0, 'Cannot zoom by 0'
        zoom_ratio = 1.2
        if delta > 0:
            zoom_factor = zoom_ratio
        else:
            zoom_factor = 1. / zoom_ratio
        camera.Zoom(zoom_factor)

    # program loop
    while window.IsOpened():
        # continuous input
        input_ = window.GetInput()

        # event based input
        event = sf.Event()
        while window.GetEvent(event):
            if event.Type == sf.Event.Closed: # close window when requested
                window.Close()
            elif event.Type == sf.Event.Resized: # resize view when requested
                width, height = window.GetWidth(), window.GetHeight()
                camera.SetHalfSize(width / 2., height / 2.)
            else:
                # mouse events
                if event.Type == sf.Event.MouseButtonPressed:
                    button = event.MouseButton.Button
                    pos = event.MouseButton.X, event.MouseButton.Y
                    x, y = real_mouse_position(*pos)
                    if button == sf.Mouse.Left:
                        if input_.IsKeyDown(sf.Key.LControl) \
                                or input_.IsKeyDown(sf.Key.RControl):
                            drawable_list = animation.current().drawable_list
                            selected = drawable_list.toggle_select(x, y)
                        elif semantic is not None:
                            start = x, y
                elif event.Type == sf.Event.MouseButtonReleased:
                    button = event.MouseButton.Button
                    pos = event.MouseButton.X, event.MouseButton.Y
                    x, y = real_mouse_position(*pos)
                    if button == sf.Mouse.Left:
                        if semantic is not None and start is not None:
                            hitbox = make_hitbox(start, (x, y), semantic)
                            if hitbox is not None:
                                dhb = DrawableHitbox(hitbox)
                                cur = animation.current()
                                drawable_list = cur.drawable_list
                                drawable_list.append(dhb)
                            semantic = None
                            start = None
                elif event.Type == sf.Event.MouseWheelMoved \
                        and input_.IsKeyDown(sf.Key.LControl) \
                        or input_.IsKeyDown(sf.Key.RControl):
                    zoomBy(event.MouseWheel.Delta)

                # key events
                if event.Type == sf.Event.KeyPressed:
                    key = event.Key.Code
                    if input_.IsKeyDown(sf.Key.LControl) \
                            or input_.IsKeyDown(sf.Key.RControl): # Ctrl + key
                        if key == sf.Key.A: # select all
                            print 'Selecting all hitboxes for current frame'
                            drawable_list = animation.current().drawable_list
                            selected = drawable_list.select_all()
                        elif key == sf.Key.C: # copy
                            print 'Copying selected hitboxes'
                            drawable_list = animation.current().drawable_list
                            copied = drawable_list.get_selected()
                        elif key == sf.Key.V: # paste
                            print 'Pasting selected hitboxes'
                            drawable_list = animation.current().drawable_list
                            for c in copied:
                                cp = c.copy()
                                print 'Pasting hitbox', repr(cp.hitbox)
                                drawable_list.append(cp)
                    elif key in semantic_mapping: # change semantic
                        new_semantic = semantic_mapping[key]
                        if len(selected) > 0 and new_semantic is not None:
                            print "Changing selected hitboxes' semantic to", \
                                    new_semantic
                            for s in selected:
                                s.set_semantic(new_semantic)
                        else:
                            print 'Switching to semantic', new_semantic
                            semantic = new_semantic
                    elif key == sf.Key.Delete: # delete selected
                        print 'Deleting selected hitboxes'
                        for s in selected:
                            drawable_list = animation.current().drawable_list
                            drawable_list.remove(s)
                        selected = []
                    elif key == sf.Key.Escape: # unselect
                        print 'Unselecting selected hitboxes'
                        drawable_list = animation.current().drawable_list
                        selected = drawable_list.clear_selection()
                    elif key == sf.Key.B: # previous frame
                        print 'Previous frame'
                        drawable_list = animation.current().drawable_list
                        animation.advance(-1)
                        selected = drawable_list.clear_selection()
                    elif key == sf.Key.N: # next frame
                        print 'Next frame'
                        drawable_list = animation.current().drawable_list
                        animation.advance(1)
                        selected = drawable_list.clear_selection()
        window.Clear()

        # get mouse position (relative to window)
        mouse = input_.GetMouseX(), input_.GetMouseY()
        mouse = real_mouse_position(*mouse)

        # move camera by continuous input
        camera_motion = [0, 0]
        if input_.IsKeyDown(sf.Key.Left):  camera_motion[0] -= 1
        if input_.IsKeyDown(sf.Key.Right): camera_motion[0] += 1
        if input_.IsKeyDown(sf.Key.Up):    camera_motion[1] -= 1
        if input_.IsKeyDown(sf.Key.Down):  camera_motion[1] += 1
        camera_motion = map(lambda x: x * 5, camera_motion)
        camera.Move(*camera_motion)

        # apply view
        window.SetView(camera)

        # draw animation
        window.Draw(animation)

        # draw current rect
        if start is not None and input_.IsMouseButtonDown(sf.Mouse.Left):
            rect = sfml_make_rect_from_corners(mouse, start)
            rect.EnableOutline(True)
            rect.EnableFill(False)
            rect.SetOutlineWidth(1)
            rect = sfml_set_rect_outline_color(rect, sf.Color.White)
            window.Draw(rect)

        # display window
        window.Display()

    # produce filename -> hitboxes dict for JSON serialization
    save_hitboxes(animation, json_file)

# Main program

def ExistingFolderType(x):
    """argparse extension as 'type' field, handling a readable folder.
    Returns the same string without trailing slashes if it exists.
    """
    if not os.path.exists(x):
        raise argparse.ArgumentError("%s doesn't exist" % x)
    elif not os.path.isdir(x):
        raise argparse.ArgumentError("%s isn't a folder" % x)
    return x.rstrip(os.path.sep)

if __name__ == '__main__':
    # command-line arguments
    parser = argparse.ArgumentParser(
            prog='HitboxMaker',
            description='Generate a hitbox descriptor for an animation')
    parser.add_argument(dest='folder', metavar='animation-folder',
            type=ExistingFolderType,
            help='Full path to the animation folder')
    parsed_args = parser.parse_args()
    animation_folder = parsed_args.folder
    json_filename = os.path.join(animation_folder, 'animation.json')
    mode = 'r+' if os.path.exists(json_filename) else 'w+'
    json_file = open(json_filename, mode)
    image_folder, animation_folder = os.path.split(animation_folder)
    main(json_file, animation_folder, image_folder)
