#!/usr/bin/env bash
# 
# Running this file will generate CTags for our project, including
# SFML 2's API as well.

# Root of our project, relative to this file
PROJECT_ROOT="."

# Headers
PROJECT_INCLUDE="$PROJECT_ROOT/include"
# ...SFML headers
SFML_INCLUDE="$PROJECT_ROOT/lib/SFML-2.0-rc/include"

# Sources
PROJECT_SRC="$PROJECT_ROOT/src"

# List of directories
API_DIRS="$PROJECT_INCLUDE $PROJECT_SRC"
if [[ -n "$WITH_SFML_TAGS" ]]; then
    echo "Including SFML 2 tags"
    API_DIRS="$API_DIRS $SFML_INCLUDE"
fi

# Tags file, relative to this file
TAGSFILE="./tags"

# CTags script
CTAGS="/usr/bin/ctags"

# CTags flags
CTAGS_FLAGS="--sort=yes --c++-kinds=+px-d --fields=+iaS --extra=+q"

# Run script
script_path=`readlink -f $0`
script_dir=`dirname $script_path`
cd "$script_dir"
if [ "$?" -eq "0" ]; then
    $CTAGS -R $CTAGS_FLAGS -f $TAGSFILE $API_DIRS
    if [ "$?" -eq "0" ]; then
        echo "Tags were generated at $script_dir/$TAGSFILE"
    else
        echo "Tags weren't generated"
    fi
else
    echo  "Couldn't change to directory $script_dir"
    exit 1
fi
