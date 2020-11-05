//
//	made by shelby on 9/15/2020
//		header file for randomly shifted grid class
//

#ifndef _RANDOM_SHIFT_
#define _RANDOM_SHIFT_

#include <vector>
#include <CGAL/Simple_cartesian.h>
#include <sdsl/suffix_trees.hpp>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;

class RandomShift
{
 private:
  //point sequences
  std::vector<Point> ptSeq1;
  std::vector<Point> ptSeq2;

  //strings
  sdsl::int_vector<> S;
  sdsl::int_vector<> T;
  sdsl::int_vector<> SxTy;
  
 public:
  //constructor
  RandomShift(std::vector<Point> p, std::vector<Point> q);

  //function to shift grid
  void shiftGrid(int g, int n);

  //functions to get strings
  sdsl::int_vector<> getS();

  sdsl::int_vector<> getT();

  sdsl::int_vector<> getSxTy();
  
private:
  //private function to push onto string vectors
  sdsl::int_vector<> push(sdsl::int_vector<> v, int i);
};

#endif //_RANDOM_SHIFT_
