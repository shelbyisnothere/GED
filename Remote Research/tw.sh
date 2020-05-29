#!/bin/bash
#script to compile past work

echo "Generating object files..."
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib DPED.cpp -o dp.o -lsdsl -ldivsufsort -ldivsufsort64
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib GreedyED.cpp -o gr.o -lsdsl -ldivsufsort -ldivsufsort64
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib SuffixTreeED.cpp -o st.o -ldsl -ldivsufsort -ldivsufsort64
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib TestWork.cpp -o m.o -ldsl -ldivsufsort -ldivsufsort64

echo "Compiling object files..."
g++ -c m.o dp.o gr.o st.o 