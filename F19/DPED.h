//
// Created by shelby on 10/28/19.
//

#ifndef GED_DPED_H
#define GED_DPED_H

#include <string>
#include <vector>

using namespace std;

class DPED
{
private:
    string w1, w2;
    vector<vector<int>> matrix;
public:
    DPED(string w1, string w2);

    int computeED();

    void printMatrix();

};
#endif //GED_DPED_H
