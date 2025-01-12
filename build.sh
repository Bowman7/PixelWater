#!/bin/bash

if [ "$1" == "--debug" ];
then
    g++ *.cpp src/*.cpp -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -g -o build/debug/run
elif [ "$1" == "--release" ];
then
    g++ *.cpp -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -O0 -o build/debug/run
elif [ "$1" == "--run" ];
then
    ./build/debug/run
elif [ "$1" == "--gdb" ];
then
    gdb ./build/debug/run 
elif [ "$1" == "--clean" ];
then
    rm */**/*.cpp~
    rm */**/*.hpp~
    rm */**/*.sh~
    rm *.cpp~
    rm *.hpp~
    rm *.sh~
else
    echo "code compiled in debug mode"
    g++ *.cpp -Wall -Isrc/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -o build/debug/run
fi
