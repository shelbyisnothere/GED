#!/bin/bash
g++ -std=c++14 -g -Wall -DNDEBUG -I ~/include -L ~/lib expl-22.cpp -o sft -lsdsl -ldivsufsort -ldivsufsort64 -lboost_serialization 
