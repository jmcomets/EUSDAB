#!/usr/bin/env bash

(cd "tests/eusdab"
if [ "$?" -eq "0" ]; then
    ../../build/tests/EUSDAB_eusdab $*
    if [ "$?" -ne "0" ]; then
        echo "Failed with exit code $?"
    fi
else
    echo "Cannot change to $test_rel_path directory"
    exit 1
fi
);
