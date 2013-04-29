#!/usr/bin/env bash

ctags -R --sort=yes --c++-kinds=+px-d --fields=+iaS --extra=+q ./include ./src \
    && echo "Tags were generated" \
|| echo "Tags weren't generated"
