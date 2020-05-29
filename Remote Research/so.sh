#!/bin/bash
g++ -std=c++11 -DNDEBUG -I ~/include -L ~/lib -c GreedyRefactored.cpp -o GR.o -lsdsl -ldivsufsort -ldivsufsort64
