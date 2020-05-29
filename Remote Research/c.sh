#!/bin/bash
./mo.sh

./so.sh

g++ -std=c++11 -DNDEBUG -I ~/include -L ~/lib main.o GR.o -o ged -lsdsl -ldivsufsort -ldivsufsort64
