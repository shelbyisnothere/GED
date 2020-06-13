//
// created by shelby on 3/6/2020
//      header file for class representing the randomly shifted grid
//      input: a point sequence
//      output: a string of Cell.h

#ifndef RANDOM_SHIFT_H
#define RANDOM_SHIFT_H

#include <CGAL/Simple_cartesian.h>
#include "Cell.h"

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Point_3 Point_3;
typedef vector<Point_2> Curve;
typedef vector<Point_3> Curve3D;


class RandomShift {
private:
    int g;                  //guess value
    int n;                  //number of points
    Curve3D pts;  //point sequence
    vector<Cell> string;    //output string



public:
    //constructor takes a curve of 2d points and guess value g
        //translates 2d points to 3d points (where all z = 0.0) for
        //planimetric grid computation
    RandomShift(Curve curve, int g);

    void shiftGrid();

    vector<Cell> getString();

};

#endif