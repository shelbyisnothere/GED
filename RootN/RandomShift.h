//
//	made by shelby on 9/15/2020
//		header file for randomly shifted grid class
//

#ifndef _RANDOM_SHIFT_
#define _RANDOM_SHIFT_

#include <vector>

class RandomShift
{
 private:
  //point sequences
  vector<Point> ptSeq1;
  vector<Point> ptSeq2;

  //strings
  vector<int> S;
  vector<int> T;

 public:
  //constructor
  RandomShift(vector<Point> p, vector<Point> q);

  //function to shift grid
  void shiftGrid(int g, int n);

  //function to get string
  vector<int> getString(char string);
}

#endif //_RANDOM_SHIFT_
