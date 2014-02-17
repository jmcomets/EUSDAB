#!/usr/bin/env bash

script_path=`readlink -f $0`
script_dir=`dirname $script_path`
(cd "$script_dir/tests/eusdab"
if [ "$?" -eq "0" ]; then
    export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
    ./eusdab map_bazar rickhard poney none none
    if [ "$?" -ne "0" ]; then
        echo "Failed with exit code $?"
    fi
else
    echo "Cannot change to $test_rel_path directory"
    exit 1
fi
);
