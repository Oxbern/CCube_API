#!/bin/bash

EXEC=../build/exec

for tests in $EXEC/*
do
    "$tests" > tmp
    if grep -q -e "TODO" tmp
    then
        echo -e "\033[33m[TODO]\033[0m pour $(basename $tests )"
    elif grep -q -e "PASSED" tmp
    then
        echo -e "\033[32m[SUCCESS]\033[0m pour $(basename $tests )"
    else
        echo -e "\033[31m[FAILED]\033[Om pour $(basename $tests)"
    fi
done
rm tmp

