//
// Created by shelby on 11/16/2019
//

#ifndef GED_SUFFIXTREEED_H
#define GED_SUFFIXTREEED_H

#include <string>
#include <sdsl/suffix_trees.hpp>
#include <vector>
#include "Elem.h"
using namespace std;

class SuffixTreeED {
private:
    int k;
    string w1, w2, AxBy;
    vector<vector<Elem>> matrix;
    Elem ED;    //cell containing edit distance
public:
    SuffixTreeED(string w1, string w2, int k);

    int computeED();

    void optimalPath();
private:
    sdsl::cst_sct3<> constructTree(string input);
};

#endif //GED_GREEDYED_H