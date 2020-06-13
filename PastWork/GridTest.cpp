/*

#include <cstdlib>

#include <iostream>
#include <fstream>
#include <vector>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>
#include <CGAL/bounding_box.h>
#include <CGAL/IO/read_ply_points.h>

using namespace std;

//typedefs i KNOW work
typedef CGAL::Simple_cartesian<double> Kernel;
//typedef Kernel::Point_2 Point_2;

//typedefs i am trying out
typedef Kernel::Point_3 Point;
typedef std::vector<Point> Point_range;
typedef CGAL::Identity_property_map<Point> Pmap;
typedef Kernel::Iso_cuboid_3 Iso_cuboid_3;

namespace Classification = CGAL::Classification;

typedef Classification::Planimetric_grid<Kernel, Point_range, Pmap> Planimetric_grid;

int main() {
    vector<Point> curve1;
    vector<Point> curve2;

    //access curve1 file
    ifstream inFile;
    inFile.open("t1_3d.txt");
    */
/*if(!inFile)
    {
        cout << "ERROR IN LOADING FILE 1";
        return 1;
    }*//*


    //read curve
    int m;  //curve length
    inFile >> m;

    cerr << "Reading input" << endl;
    if (!inFile
        || !(CGAL::read_ply_points (inFile, std::back_inserter (curve1))))
    {
        std::cerr << "Error: cannot read file" << std::endl;
        return EXIT_FAILURE;
    }

    */
/*for(int i = 0; i < m; i++)
    {
        float x, y;
        inFile >> x >> y;
        Point_2 p(x, y);
        curve1.push_back(p);
    }*//*


    inFile.close();

    //access curve 2 file
    inFile.open("t2_3d.txt");
    */
/*if(!inFile)
    {
        cout << "ERROR IN LOADING FILE 2";
        return 1;
    }*//*


    //read curve
    inFile >> m;

    cerr << "Reading input" << endl;
    if (!inFile
        || !(CGAL::read_ply_points (inFile, std::back_inserter (curve1))))
    {
        std::cerr << "Error: cannot read file" << std::endl;
        return EXIT_FAILURE;
    }

    */
/*for(int i = 0; i < m; i++)
    {
        float x,y;
        inFile >> x >> y;
        Point_2 p(x, y);
        curve2.push_back(p);
    }*//*


    inFile.close();

    float grid_resolution = 0.34f;
    Iso_cuboid_3 bbox = CGAL::bounding_box(curve1.begin(), curve1.end());

    //load grid
    Planimetric_grid grid(curve1, Pmap(), bbox, grid_resolution);

    cout << "\n**************TEST*************";
    cout << "\nx points: " << grid.width();
    cout << "\ny points " << grid.height();
    cout << "\nthird point: (" << grid.x(2) << ", " << grid.y(2) << ") ";



    return 0;
}*/
#if defined (_MSC_VER) && !defined (_WIN64)
#pragma warning(disable:4244) // boost::number_distance::distance()
                              // converts 64 to 32 bits integers
#endif
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>
#include <CGAL/bounding_box.h>
#include <CGAL/IO/read_ply_points.h>
#include <CGAL/Real_timer.h>
#ifdef CGAL_LINKED_WITH_TBB
typedef CGAL::Parallel_tag Concurrency_tag;
#else
typedef CGAL::Sequential_tag Concurrency_tag;
#endif
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef Kernel::Iso_cuboid_3 Iso_cuboid_3;
typedef std::vector<Point> Point_range;
typedef CGAL::Identity_property_map<Point> Pmap;
namespace Classification = CGAL::Classification;
typedef Classification::Sum_of_weighted_features_classifier Classifier;
typedef Classification::Planimetric_grid<Kernel, Point_range, Pmap>             Planimetric_grid;
typedef Classification::Point_set_neighborhood<Kernel, Point_range, Pmap>       Neighborhood;
typedef Classification::Local_eigen_analysis                                    Local_eigen_analysis;
typedef Classification::Label_handle                                            Label_handle;
typedef Classification::Feature_handle                                          Feature_handle;
typedef Classification::Label_set                                               Label_set;
typedef Classification::Feature_set                                             Feature_set;
typedef Classification::Feature::Distance_to_plane<Point_range, Pmap>           Distance_to_plane;
typedef Classification::Feature::Elevation<Kernel, Point_range, Pmap>           Elevation;
typedef Classification::Feature::Vertical_dispersion<Kernel, Point_range, Pmap> Dispersion;
int main (int argc, char** argv)
{
    std::string filename (argc > 1 ? argv[1] : "t1_3d.ply");
    std::ifstream in (filename.c_str());
    std::vector<Point> pts;
    std::cerr << "Reading input" << std::endl;
    if (!in
        || !(CGAL::read_ply_points (in, std::back_inserter (pts))))
    {
        std::cerr << "Error: cannot read " << filename << std::endl;
        return EXIT_FAILURE;
    }
    float grid_resolution = 0.34f;
    unsigned int number_of_neighbors = 6;
    std::cerr << "Computing useful structures" << std::endl;
    Iso_cuboid_3 bbox = CGAL::bounding_box (pts.begin(), pts.end());
    Planimetric_grid grid (pts, Pmap(), bbox, grid_resolution);
    std::cerr << "All done" << std::endl;
    return EXIT_SUCCESS;
}

