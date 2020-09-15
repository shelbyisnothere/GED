//
//	made by shelby on 9/14/2020
//		main c++ file for O(root(n)) approximation
//

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <CGAL/squared_distance_3.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/IO/read_xyz_points.h>

using namespace std;

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;

int main(int argc, char * argv[]){
  //load data points
  vector<Point> p;
  vector<Point> q;
  double x, y;
  int np, nq;
  
  ifstream inFile;
  //read p
  inFile.open(argv[1]);
  if(!inFile.is_open())
    cerr << "Unable to open data file 1. \nFile name: " << argv[1];

  cout << "\nReading file: " << argv[1] << endl;

  inFile >> np;
  
  while(inFile >> x >> y)
  {
    Point point(x, y, 0);
    p.push_back(point);
  }
  
  inFile.close();

  //read q
  inFile.open(argv[2]);
  if(!inFile.is_open())
    cerr << "Unable to open data file 2. \nFile name: " << argv[2];

  cout << "\nReading file: " << argv[2] << endl;

  inFile >> y;
  
  while(inFile >> x >> y)
  {
    Point point(x, y, 0);
    p.push_back(point);
  }

  inFile.close();
  
  //begin algorithm 1
  bool tmp;	//place holder for dist(p, q)
  int g;	//guess value
  bool out;	//for SED
  double sum;
  
  for(int i = 0; i < min(np, nq); i++) {
    sum += CGAL::sqrt(CGAL::squared_distance(p[i], q[i]));
  }

  if(sum < 0){
    //return matching?
  }
  else {
    for(int i = 0; i < log(CGAL::sqrt(min(np, nq))); i++){
      g = pow(2, i);
      //transform p ad q to strings
      //out = SED(s, t, 12root(n) + 2g)
      if(!(out == false)){
	//return out??
      }
    }
  }*/

  //return empty matching
  return 0;
}
