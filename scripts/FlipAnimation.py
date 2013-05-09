#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import argparse
import json
from PIL import Image

json_file_basename = 'animation.json'
out_folder_suffix = 'out'

def main(in_folder):
    out_folder = os.path.join(in_folder, out_folder_suffix)
    try:
        in_json = os.path.join(in_folder, json_file_basename)
        if not os.path.exists(out_folder):
            os.mkdir(out_folder)
        out_json = os.path.join(out_folder, json_file_basename)
        dct = json.load(open(in_json, 'r'))
        frames = dct['frames']
        for filename, hitbox_list in frames.items():
            for hb in hitbox_list:
                hb['center']['x'] *= -1.
            in_filename = os.path.join(in_folder, filename)
            out_filename = os.path.join(out_folder, filename)
            img = Image.open(in_filename)
            img = img.transpose(Image.FLIP_LEFT_RIGHT)
            img.save(out_filename)
        json.dump(dct, open(out_json, 'w'))
    except IOError, OSError:
        print e

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
            prog='Animation flipper',
            description='Flip an image along its central vertical axis')
    parser.add_argument('in_folder', metavar='animation',
            help="Folder containing the animation images and JSON descriptor")
    parsed_args = parser.parse_args()
    main(**vars(parsed_args))
