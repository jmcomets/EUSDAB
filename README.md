The Epic Ultimate Showdown of Doom for Awesome Badassness
=========================================================

2D Platform-Fighting Game written in C++11 / Python

Known issues
------------

* knockback not balanced (too low)
* death not possible
* Pedro Panda's hitbox is too big
* Pedro Panda's UpB and DownB not handled
* Poney's DownA not handled

Project setup
-------------

* demo - small demo written to present EUSDAB
* scripts - various scripts used in development
* include - header files
* src - source files
* tests - executable tests (all built with CMake)
* assets - images, sounds, etc...
* lib - SFML binaries

Requirements
------------

EUSDAB is build with [CMake][1]

* Boost 1.4+
* SFML 2.0+
* SFML dependencies :
    - pthread
    - opengl
    - xlib
    - xrandr
    - freetype
    - glew
    - jpeg
    - sndfile
    - openal

If you have any trouble building, check [here][2] for more details
on SFML's requirements.

Building
--------

```bash
cd /path/to/eusdab
cmake . # for a basic build (adds temp CMake files in the project tree)
mkdir build && cd build && cmake .. # for an out-of-source build
make eusdab # or just "make" if you want to build all the tests
```

[1]: http://www.cmake.org/
[2]: http://www.sfml-dev.org/tutorials/2.0/compile-with-cmake.php
