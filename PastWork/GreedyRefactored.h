// created by Shelby on 1/31

#ifndef GREEDY_REFACTORED_H
#define GREEDY_REFACTORED_H

#include <CGAL/Simple_cartesian.h>
#include <vector>
#include "Cell.h"
#include "Elem.h"

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;

class GreedyRefactored
{
private:
    int k;      //threshold
    std::vector<Cell> curve1, curve2;
    std::vector<std::vector<Elem>> matrix;  //store ED computations to trace alignment
    Elem ED;    //edit distance

public:
    GreedyRefactored(std::vector<Cell> curve1, std::vector<Cell> curve2, int k);
    //computes edit distance
    int computeED();
    //retrieves optimal path
    std::vector<Point_2> getAlignment();

private:
    //computes slide, returning row of last entry along diagonal
    int slide(int i, int j);
};

#endif