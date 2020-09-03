#include "DPED.h"
#include "GreedyED.h"
#include "SFED.h"
#include <string>
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

typedef SuffixTreeED SFED;

/*TO COMPILE ON LINUX TERMINAL:
 g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib main.cpp -o ged DPED.h GreedyED.h DPED.cpp GreedyED.cpp SuffixTreeED.h SuffixTreeED.cpp Elem.h -lsdsl -ldivsufsort -ldivsufsort64
 * ************************/
//using namespace std::chrono;
using namespace std;


int main()
{
    ifstream inFile;
    inFile.open("words.txt");
    int k;
    string w1, w2;
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    while(!inFile.eof())
    {
        inFile >> k;
        inFile >> w1;
        inFile >> w2;

        DPED testDP(w1, w2);
        GreedyED testGreedy(w1, w2, k);
        SuffixTreeED testSuffix(w1, w2, k);
        cout << "DYNAMIC PROGRAMMING ALG: \n";
        auto start = std::chrono::high_resolution_clock::now();
        cout << testDP.computeED() << endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time: " << duration.count() << " microseconds" << endl;

        cout << endl << endl;
        cout << "GREEDY ALG: \n";
        start = std::chrono::high_resolution_clock::now();
        cout << testGreedy.computeED() << endl;
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time: " << duration.count() << " microseconds";

        //testGreedy.optimalPath();

        cout << endl << endl;
        cout << "SUFFIX TREE ALG: \n";
        start = std::chrono::high_resolution_clock::now();
        cout << testSuffix.computeED() << endl;
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time: " << duration.count() << " microseconds";

        //testSuffix.optimalPath();

        cout << endl;
    }

}


