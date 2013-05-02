#!/usr/bin/env bash
#
# This script helps out when running EUSDAB, without any
# arguments it will run_test the main EUSDAB project, but will run_test
# all existing tests given in command-line arguments sequentially,
# also changing CWD to the correct one.

# The name of our project
PROJECT_NAME='EUSDAB'

# CMake build directory
BUILD_DIR='./build'

# Project tests directory storing all of our tests
TESTS_DIR='./tests'

# Run script
if [ "$#" -eq "0" ]; then
    if [ -f "$BUILD_DIR/$PROJECT_NAME" ]; then
        "$BUILD_DIR/$PROJECT_NAME"
    else
        echo "Cannot find $BUILD_DIR/$PROJECT_NAME, consider recompiling"
        exit 1
    fi
else
    for test_name in $*; do
        exe_name="$PROJECT_NAME""_""$test_name"
        test_rel_path="$TESTS_DIR/$test_name"
        exe_rel_path="$TESTS_DIR/$exe_name"
        exe_full_path=`readlink -e "$BUILD_DIR/$exe_rel_path"` 
        if [ "$?" -eq "0" ]; then
            cd "$test_rel_path" && "$exe_full_path"
        else
            echo "Cannot find $BUILD_DIR/$exe_rel_path, consider recompiling"
        exit 1
        fi
    done
fi
