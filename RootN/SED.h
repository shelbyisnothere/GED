//
//	made by shelby on 2 October 2020
//		header file for string edit distance class
//

#ifndef _SED_H_
#define _SED_H_

#include <sdsl/suffix_trees.hpp>
//#include <CGAL/Simple_cartesian.h>
#include <sdsl/int_vector.hpp>
#include <vector>
#include "Elem.h"

//typedef CGAL::Simple_cartesian<double> Kernel;
//typedef Kernel::Point_3 Point;

class SED
{
 private:
  sdsl::int_vector<> A;		//first string
  sdsl::int_vector<> B;		//second string
  sdsl::int_vector<> AxBy;	//concatenated strings
  int k;			//guess value
  std::vector<std::vector<Elem>> matrix;
  Elem ED;			//edit distance

 public:
  //constructor
  SED(sdsl::int_vector<> AxBy, int k);

  //to compute edit distance
  int computeED();

  //retrieve the optimal path
  //  std::vector<Point> optimalPath();
};

#endif //_SED_H_
