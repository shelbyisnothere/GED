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
#include <CGAL/Aff_transformation_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/aff_transformation_tags.h>
#include <random>

using namespace std;

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef std::vector<Point> Point_range;
typedef CGAL::Identity_property_map<Point> Pmap;
typedef Kernel::Iso_cuboid_3 Iso_cuboid_3;
typedef CGAL::Classification::Planimetric_grid<Kernel, Point_range, Pmap> Planimetric_grid;
typedef Kernel::Vector_3 Vector_3;
typedef CGAL::Aff_transformation_3<Kernel> Affine_transformation_3;

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

	float grid_resolution = 1.0f;
	Iso_cuboid_3 bbox = CGAL::bounding_box(curve1.begin(), curve1.end());
	cout << "\nBounding box computed successfully.\n";
	Planimetric_grid beforeShift(curve1, Pmap(), bbox, grid_resolution);
	cout <<"Grid computer successfully.\n\n";
	//shift grid for testing purposes
	cout << "Shifting grid...\n";
	random_device r;
	default_random_engine e1(r());
	uniform_real_distribution<float> choose(0, grid_resolution);
	float random = choose(e1);
	cout << "\tShifting grid by: " << random << endl;
	Point o(0, 0, 0);
	Point x(random, 0, 0);
	Point y(0, random, 0);
	Vector_3 hor(o, x);
	Vector_3 vert(o, y);
	Affine_transformation_3 horTrans(CGAL::TRANSLATION, hor);
	Affine_transformation_3 verTrans(CGAL::TRANSLATION, vert);
	bbox = bbox.transform(horTrans);
	bbox = bbox.transform(verTrans);
	Planimetric_grid afterShift(curve1, Pmap(), bbox, grid_resolution);
	cout << "Shifted grid computed successfully...\n\n";
	
	//query grid
	vector<int> S;
	vector<int> T;
	int character;

	for(int i = 0; i < curve1.size(); i++)
	  {
	    if(i < p)
	      {
		cout << beforeShift.x(i) << " " << beforeShift.y(i) << endl;
		character = beforeShift.x(i) + beforeShift.y(i);
		S.push_back(character);
	      }
	    else
	      {
		cout << beforeShift.x(i) << " " << beforeShift.y(i) << endl;		
		character = beforeShift.x(i) + beforeShift.y(i);
		T.push_back(character);
	      }
	  }

	//query SHIFTED grid
	vector<int> Sshifted;
	vector<int> Tshifted;
	cout << endl << endl;
	for(int i = 0; i < curve1.size(); i++)
	  {
	    if(i < p)
	      {
	        cout << afterShift.x(i) << " " << afterShift.y(i) << endl;
		character = afterShift.x(i) + afterShift.y(i);
		Sshifted.push_back(character);
	      }
	    else
	      {
	        cout << afterShift.x(i) << " " << afterShift.y(i) << endl;
		character = afterShift.x(i) + afterShift.y(i);
		Tshifted.push_back(character);
	      }
	  }

	
	//write unshifted grid string to file
	ofstream out;

	out.open("data/string.text");

	out << "=====GRID=====\n";
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

	out << "\n\n=====SHIFTED GRID=====\n";
	i = 0;
	for(int c : Sshifted)
	  {
	    out << c << "\t" << Tshifted[i] << endl;
	    i++;
	  }

	out.close();
	cout << "\n\nData written to: data/string.txt";
}
