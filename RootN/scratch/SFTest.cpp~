#include <iostream>
#include <vector>
#include <string>
#include <sdsl/suffix_trees.hpp>
//#include <sdsl/int_vector.hpp>

using namespace sdsl;
using namespace std;

int main()
{
  //vector <int> s = {1, 2, 1, 3, 2, 1, 4, 5, 1, 2, 1, 6, 2, 1, 2};
  cst_sct3<csa_wt<wt_int<rrr_vector<>>>> cst;
  int_vector<> data(100000, 0, 10);
  construct_im(cst, data);
  /*  cout << "inner nodes : " << cst.nodes() - cst.csa.size() << endl;
  auto v = cst.select_child(cst.child(cst.root(), 'u'), 1);
  auto d = cst.depth(v);
  cout << "v: " << d << "-[" << cst.lb(v) << "," << cst.rb(v) << "]" << endl;
  cout << "extract(cst, v) : " << extract(cst, v) << endl;
 
  */

  for (size_t i=0; i < data.size(); ++i)
    data[i] = 1 + rand()%1023;
  construct_im(cst, data);
  cout << "cst.csa.sigma: " << cst.csa.sigma << endl;
  for (size_t k=0; k<3; ++k)
    cout << "H" << k << "(data) : " <<  get<0>(Hk(cst, k)) << endl;

  return 0;
}
