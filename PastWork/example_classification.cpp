#if defined (_MSC_VER) && !defined (_WIN64)
#pragma warning(disable:4244) // boost::number_distance::distance()
                              // converts 64 to 32 bits integers
#endif

#include <cstdlib>
#include <iostream>
#include <string>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>
#include <CGAL/bounding_box.h>

#include <CGAL/IO/write_xyz_points.h>
#include <CGAL/IO/read_xyz_points.h>

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


///////////////////////////////////////////////////////////////////
//! [Analysis]

class iterator;

class iterator;

int main (int argc, char** argv)
{
  std::string filename (argc > 1 ? argv[1] : "data/points.xyz");
  std::ifstream in (filename.c_str());
  std::vector<Point> pts;

  std::cerr << "Reading input" << std::endl;
  if (!in
      || !(CGAL::read_xyz_points (in, std::back_inserter (pts))))
  {
    std::cerr << "Error: cannot read " << filename << std::endl;
    return EXIT_FAILURE;
  }

    int curveSize1 = pts.size();
    //shift points in x
    for(int i = 0; i < curveSize1; i++)
    {
        double x = pts[i].x() + 0.17;
        Point p(x, pts[i].y(), pts[i].z());
        pts.push_back(p);

    }

    int curveSize2 = pts.size();

    //shift points in y
    for(int i = curveSize1 - 1; i < curveSize2; i++)
    {
        double y = pts[i].y() + 0.17;
        Point p(pts[i].x(), y, pts[i].z());
        pts.push_back(p);
    }

    std::cerr << "Writing shifted points" << std::endl;

  std::ofstream out("data/test_shift.xyz");

    if(!out || !(CGAL::write_xyz_points(out, pts)))
    {
        std::cerr << "Error: cannot write file" << std::endl;
        return 1;
    }

  out.close();

  float grid_resolution = 2.0f;        //this should be delta!!!
  unsigned int number_of_neighbors = 6;

  std::cerr << "Computing planimetric grid" << std::endl;

  Iso_cuboid_3 bbox = CGAL::bounding_box (pts.begin(), pts.end());

  Planimetric_grid grid (pts, Pmap(), bbox, grid_resolution);


  //for(auto it = grid.indices_begin(0, 0); !it.equal(grid.indices_end(grid.width(), grid.height())); it.increment())
  for(int i = 0; i < grid.width(); i++)
  {
      for(int j = 0; j < grid.height(); j++)
      {
          if(grid.has_points(i, j))
              std::cout << "\n(" << i << ", " << j << ")";
      }

  }
  
  std::cerr << "All done" << std::endl;
  return EXIT_SUCCESS;
}