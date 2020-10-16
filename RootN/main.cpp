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
#include <CGAL/number_utils.h>
#include "RandomShift.h"

using namespace std;

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;

int main(int argc, char * argv[]){
  //load data points
  vector<Point> p;
  vector<Point> q;	
  double x, y;		//for loading in individual points
  int np, nq;		//overall number of points in p and q
  
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

  inFile >> nq;
  
  while(inFile >> x >> y)
  {
    Point point(x, y, 0);
    q.push_back(point);
  }

  inFile.close();
  
  //begin algorithm 1
  bool tmp;		//place holder for dist(p, q)
  int g;		//guess value
  bool out;		//for SED
  double sum;
  sdsl::int_vector<> S;
  sdsl::int_vector<> T;
  double c = 1.0;	//sufficiently large c
  
  cout << "\nComparing sum of distance between points..." << endl;
  for(int i = 0; i < min(np, nq); i++) {
    sum += CGAL::sqrt(CGAL::squared_distance(p[i], q[i]));
  }

  if(np != nq)
    {//cant return matching w uneven strings(?)
      sum = 1;
    }
  if(sum < 1){
    //return matching?
  }
  else {
    cout << "\nConverting to strings S and T, and comparing edit distance..." << endl;
    for(int i = 0; i < log(sqrt(max(np, nq))); i++){
      g = pow(2, i);
      for(int j = 0; j < c * log(max(np, nq)); j++)
	{
	  //transform p and q to strings
	  RandomShift shift(p, q);
	  shift.shiftGrid(g, max(np, nq));
	  S = shift.getS();
	  T = shift.getT();
	  cout << endl << S.size() << " " << T.size();
	  //SED
	  //if(!out)
	}
    }//end outer for

    //return empty matching
    
  }//end else

  for(size_t i = 0; i < S.size(); i++)
    {
      cout << S[i] << " ";
    }
  for(size_t i = 0; i < T.size(); i++)
    {
      cout << T[i] << " ";
    }
  
  return 0;
}
