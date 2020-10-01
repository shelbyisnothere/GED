#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <cstdlib>
#include <iostream>
#include <fstream> 
#include <string>
#include <vector> 
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>
#include <CGAL/bounding_box.h>	
#include <CGAL/IO/read_xyz_points.h>

using namespace std;

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef std::vector<Point> Point_range;
typedef CGAL::Identity_property_map<Point> Pmap;
typedef Kernel::Iso_cuboid_3 Iso_cuboid_3;
typedef CGAL::Classification::Planimetric_grid<Kernel, Point_range, Pmap> Planimetric_grid;

int main() {
	Point_range curve1;
	Point_range curve2;

	ifstream inFile;
	inFile.open("t1_3d.txt");
	if(!inFile) {
		cout <<"ERROR LOADING FILE 1";
		return 1;
	}

	//read first curve
	cerr << "\nReading input 1";
	if(!inFile || !(CGAL::read_xyz_points (inFile, std::back_inserter (curve1))))
	{
		cerr << "Error: cannot read file\n";
		return EXIT_FAILURE;
	}
	inFile.close();

	//track size of first curve
	int p = curve1.size();
	
	inFile.open("t2_3d.txt");
	//read second curve
	cerr << "\nReading input 2";
	if(!inFile || !(CGAL::read_xyz_points (inFile, std::back_inserter (curve1))))
	{
		cerr << "Error: cannot read file\n";
		return EXIT_FAILURE;
	}
	inFile.close();

	float grid_resolution = 0.34f;
	Iso_cuboid_3 bbox = CGAL::bounding_box(curve1.begin(), curve1.end());
	cout << "\nBounding box computed successfully.";
	Planimetric_grid grid(curve1, Pmap(), bbox, grid_resolution);

	//query grid
	vector<int> S;
	vector<int> T;
	int character;

	for(int i = 0; i < curve1.size(); i++)
	  {
	    if(i < p)
	      {
		character = grid.x(i) + grid.y(i);
		S.push_back(character);
	      }
	    else
	      {
		character = grid.x(i) + grid.y(i);
		T.push_back(character);
	      }
	  }
	
	//write unshifted grid string to file
	ofstream out;

	out.open("data/string.text");

	if(!out)
	  {
	    cerr << "Error opening file";
	    return 1;
	  }
	int i = 0;
	for(int c : S)
	  {
	    out << c << "\t" << T[i] << endl;
	    i++;
	  }
	out.close();
}
