//
//	made by shelby on 9/15/2020
//		header file for randomly shifted grid class
//

#ifndef _RANDOM_SHIFT_
#define _RANDOM_SHIFT_

#include <vector>
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;

class RandomShift
{
 private:
  //point sequences
  std::vector<Point> ptSeq1;
  std::vector<Point> ptSeq2;

  //strings
  std::vector<int> S;
  std::vector<int> T;
  
 public:
  //constructor
  RandomShift(std::vector<Point> p, std::vector<Point> q);

  //function to shift grid
  void shiftGrid(int g, int n);

  //function to get string
  std::vector<int> getString(char string);
}

#endif //_RANDOM_SHIFT_
