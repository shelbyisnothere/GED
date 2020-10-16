//
//	made by shelby on 17 September 2020
//		source file for randomly shifting grid
//
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <iostream>
#include <vector>
//#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>
#include <CGAL/bounding_box.h>
#include <CGAL/Aff_transformation_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/aff_transformation_tags.h>
#include <random>
#include <algorithm>
#include "RandomShift.h"

using namespace std;
using namespace sdsl;

//typedef CGAL::Simple_cartesian<double> Kernel;
//typedef Kernel::Point_3 Point;
typedef std::vector<Point> Point_range;
typedef CGAL::Identity_property_map<Point> Pmap;
typedef Kernel::Iso_cuboid_3 Iso_cuboid_3;
typedef CGAL::Classification::Planimetric_grid<Kernel, Point_range, Pmap> Planimetric_grid;
typedef Kernel::Vector_3 Vector;
typedef CGAL::Aff_transformation_3<Kernel> Transform;

//
//	constructor
//
RandomShift::RandomShift(vector<Point> ptSeq1, vector<Point> ptSeq2)
  :ptSeq1(ptSeq1), ptSeq2(ptSeq2)
{
  S.resize(0);
  T.resize(0);
}

//
//	function to perform shift on pts and compute S and T
//
void RandomShift::shiftGrid(int g, int n){
  vector<Point> pts;
  //concatenate pt sequences p & q to put in PGrid
  pts.reserve(ptSeq1.size() + ptSeq2.size());
  pts.insert(pts.end(), ptSeq1.begin(), ptSeq1.end());
  pts.insert(pts.end(), ptSeq2.begin(), ptSeq2.end());

  //create bounding box
  Iso_cuboid_3 bbox = CGAL::bounding_box(pts.begin(), pts.end());

  //set delta (aka cell width)
  float delta = g / (sqrt(n));
  
  //shift bounding box
  	//choose uniform random vector
  random_device r;
  default_random_engine e1(r());
  uniform_real_distribution<float> choose(0, delta);
  float random = choose(e1);

  	//set vectors for transformation
  Point o(0, 0, 0);
  Point x(random, 0, 0);
  Point y(0, random, 0);
  Vector hor(o, x);
  Vector vert(o, y);

  	//shift
  Transform horShift(CGAL::TRANSLATION, hor);
  Transform vertShift(CGAL::TRANSLATION, vert);
  Iso_cuboid_3 shiftedBbox;
  shiftedBbox = bbox.transform(horShift);
  shiftedBbox = shiftedBbox.transform(vertShift);
  
  //create Pgrid
  Planimetric_grid grid(pts, Pmap(), shiftedBbox, delta);  
  
  //query grid to get string s & t
  int character;
  int max = std::max(grid.width(), grid.height());
  
  for(int i = 0; i < pts.size(); i++)
    {
      //create unique chracter for string at index i
      	// below diagonal = negative integer
      	// above diagonal = positive integer
      	// on diagonal = mx(grid width, grid height) + grid.x()
      character = grid.x(i) - grid.y(i);
      if(character == 0)
	{
	  character = max + grid.x(i);
	}
      //append character to respective string
      if(i < ptSeq1.size())
	{
	  S = push(S, character);
	}
      else
	{
	  T = push(T, character);
	}
    }
}

//
// function to get string S
//
int_vector<> RandomShift::getS()
{
  return S;
}

//
// function to get string T
//
int_vector<> RandomShift::getT()
{
  return T;
}

//
// function to push onto a string
//
int_vector<> RandomShift::push(int_vector<> v, int i)
{
  int_vector<> tmp;
  tmp = v;
  tmp.resize(v.size() + 1);
  tmp[tmp.size() - 1] = i;
  return tmp;
}
