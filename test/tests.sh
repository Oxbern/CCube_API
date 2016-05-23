#!/bin/bash

# On se place dans le répertoire du projet (quel que soit le
# répertoire d'où est lancé le script) :
cd "$(dirname "$0")"/../build/exec || exit 1

for tests in $(ls)
do
    $(./"$tests" > tmp)

    if grep -q -e "TODO" tmp
    then
        tput setaf 3;
        echo -e "[TODO] for $(basename $tests)"
    elif grep -q -e "PASSED" tmp
    then
        tput setaf 2;
        echo -e "[SUCCESS] for $(basename $tests)"
    else
        tput setaf 1;
        echo -e "[FAILED] for $(basename $tests)"
    fi
    tput setaf 7;
done
rm tmp