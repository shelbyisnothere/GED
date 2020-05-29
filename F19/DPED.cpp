//
// Created by shelby on 10/28/19.
//

#include "DPED.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

DPED::DPED(string w1, string w2)
        : w1(w1), w2(w2)
{}

int DPED::computeED() {
    vector<int> prev;
    vector<int> curr;

    //first row
    for(int j = 0; j <= w2.length(); j++)
    {
        prev.push_back(j);
    }

    matrix.push_back(prev);

    for(int i = 1; i <= w1.length(); i++)
    {
        //first column
        curr.push_back(prev[0] + 1);

        //next row
        for(int j = 1; j <= w2.length(); j++)
        {
            int delta;
            if (w1[i - 1] == w2[j - 1])
                delta = 0;
            else
                delta = 1;

            int up = prev[j] + 1;
            int left = curr[j - 1] + 1;
            int diagonal = prev[j - 1] + delta;
            curr.push_back(std::min(up, std::min(left, diagonal)));
        }
        matrix.push_back(curr);

        //update vectors
        for (int i = 0; i < curr.size(); i++)
        {
            prev[i] = curr[i];
        }
        curr.clear();
    }
    return matrix[w1.length()][w2.length()];
}

void DPED::printMatrix() {
    for(vector<int> row : matrix)
    {
        for(int val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}