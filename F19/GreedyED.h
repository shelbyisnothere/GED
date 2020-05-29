//
// Created by shelby on 10/28/19.
//

#ifndef GED_GREEDYED_H
#define GED_GREEDYED_H

#include <string>
#include <vector>
#include "Elem.h"

using namespace std;

class GreedyED
{
private:
    int k;      //threshold
    string w1, w2;
    vector<vector<Elem>> matrix;
    Elem ED;    //cell containing edit distance

public:
    //constructor
    GreedyED(string w1, string w2, int k);

    int computeED();

    void optimalPath();

private:
    int slide(int i, int j);
};

#endif //GED_GREEDYED_H
