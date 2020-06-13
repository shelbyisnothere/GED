//
// Created by shelby on 10/28/19.
//

#ifndef GED_GREEDYED_H
#define GED_GREEDYED_H

#include <string>
#include <vector>
#include "Elem.h"
//CGAL STUFF
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;

using namespace std;

class GreedyED
{
private:
    int k;      //threshold
    string w1, w2;
    vector<vector<Elem>> matrix;
    Elem ED;    //cell containing edit distance
    vector<Point_2> alignment;

public:
    //constructor
    GreedyED(string w1, string w2, int k);

    int computeED();

    void optimalPath();

    vector<Point_2> getAlignment();

private:
    int slide(int i, int j);
};

#endif //GED_GREEDYED_H
