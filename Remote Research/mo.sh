#!/bin/bash
g++ -std=c++11 -DNDEBUG -I ~/include -L ~/lib -c main.cpp -o main.o -lsdsl -ldivsufsort -ldivsufsort64
