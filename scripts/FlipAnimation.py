#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
from PIL import Image

def main(in_filename, out_filename):
    try:
        img = Image.open(in_filename).transpose(Image.FLIP_LEFT_RIGHT)
        img.save(out_filename)
    except IOError as e:
        print e

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
            prog='Image flipper',
            description='Flip an image along its central vertical axis')
    parser.add_argument('in_filename', metavar='input',
            help='Source image path')
    parser.add_argument('out_filename', metavar='output',
            help='Output image path')
    parsed_args = parser.parse_args()
    main(**vars(parsed_args))
