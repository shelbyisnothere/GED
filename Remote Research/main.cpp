#include <iostream>
#include <vector>
#include <fstream>
#include <CGAL/Simple_cartesian.h>
#include "Cell.h"
#include "GreedyRefactored.h"

using namespace std;

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;


int main() {
    /*vector<Point_2> curve1;
    vector<Point_2> curve2;*/
    vector<Cell> curve1;
    vector<Cell> curve2;

    //access curve1 file
    ifstream inFile;
    inFile.open("t1.txt");
    if(!inFile)
    {
        cout << "ERROR IN LOADING FILE 1";
        return 1;
    }

    //read curve
    int m;  //curve length
    inFile >> m;

    for(int i = 0; i < m; i++)
    {
        //doube x, y;
        float x, y;
        inFile >> x >> y;
        //Point_2 p(x, y);
        curve1.push_back({x, y});
    }

    inFile.close();

    //access curve 2 file
    inFile.open("t2.txt");
    if(!inFile)
    {
        cout << "ERROR IN LOADING FILE 2";
        return 1;
    }

    //read curve
    inFile >> m;

    for(int i = 0; i < m; i++)
    {
        float x,y;
        //double x, y;
        inFile >> x >> y;
        //Point_2 p(x, y);
        curve2.push_back({x, y});
    }

    inFile.close();

    GreedyRefactored test(curve1, curve2, 10);

    cout << "ED is " << test.computeED() << endl;

    vector<Point_2> alignment = test.getAlignment();

   if(test.computeED() != -1)
    {
        cout << "Alignment: \n";
        for(Point_2 p : alignment)
        {
            cout << p.x() << " " << p.y() << endl;
        }
    }


    return 0;
}