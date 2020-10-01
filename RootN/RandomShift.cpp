//
//	made by shelby on 17 September 2020
//		source file for randomly shifting grid
//
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <iostream>
#include <vector>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>
#include <CGAL/bounding_box.h>
#include "RandomShift.h"

using namespace std;

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef std::vector<Point> Point_range;
typedef CGAL::Identity_property_map<Point> Pmap;
typedef Kernel::Iso_cuboid_3 Iso_cuboid_3;
typefed CGAL::Classification::Plantimetric_grid<Kernel, Point_range, Pmap> Planimetric_grid;

//
//	constructor
//
RandomShift::RandomShift(vector<Point> ptSeq1, vector<Point> ptSeq2)
  :ptSeq1(ptSeq1), ptSeq2(ptSeq2)
{}

//
//	function to perform shift on pts and compute S and T
//
void RandomShift::shiftGrid(int g, int n){
  vector<Point> pts;
  //concatenate pt sequences p & q to put in PGrid
  pts.reserve(ptSeq1.size() + ptSeq2.siz());
  pts.insert(pts.end(), ptSeq1.begin(), ptSeq1.end());
  pts.insert(pts.end(), ptSeq2.begin(), ptSeq2.end());

  //create bounding box
  Iso_cuboid_3 bbox = CGAL::bounding_box(pts.begin(), pts.end());

  //set grid resolution - delta(?)
  float grid_resolution = g / (CGAL::sqrt(n));
  
  //create Pgrid
  Planitmetric_grid grid(curve1, Pmap(), bbox, grid_resolution);  
  
  //query grid to get string s & t
  int character;
  for(int i = 0; i < pts.size(); i ++)
    {
      //create unique chracter for string at index i
      character = grid.x(i) + grid.y(i);
      //append character to respective string
      if(i < ptSeq1.size())
	{
	  S.push_back(character);
	}
      else
	{
	  T.push_back(character);
	}
    }
}

//
//	function to get a single string
//		either S or T
//
vector<int> getString(char string)
{
  if(string = 'S')
    {
      return S;
    }
  else if(string = 'T')
    {
      return T;
    }
  //other wise return empty string
  vector<int> emptyString;
  return emptyString;
}
