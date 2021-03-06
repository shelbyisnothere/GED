#include <sdsl/suffix_trees.hpp>
#include <iostream>
#include <vector>

using namespace sdsl;
using namespace std;

int_vector<> push(int_vector<> v, int i)
{
  int_vector<> tmp;
  tmp = v;
  tmp.resize(v.size() + 1);
  tmp[tmp.size() - 1] = i;
  return tmp;
}

int main()
{
  int_vector<> vec = {1, 2, 1, 3, 2, 1, 4, 5, 1, 2, 1, 3, 2, 1, 2};
  cst_sct3<csa_wt<wt_int<rrr_vector<>>>> cst;
  construct_im(cst, vec);

  vec = push(vec, -2);
  vec = push(vec, -1);

  //cout << vec[vec.size() - 2] << endl;
  //cout << vec[vec.size() - 1] << endl;
  //leaftable
  vector<int> leafTable(vec.size() + 1, 0);
  cout << vec.size() << endl << endl;
  for(int i = 1; i <= vec.size() + 1; i++)
    {
      auto v = cst.select_leaf(i);
      int index = vec.size() - cst.depth(v) + 1;
      cout << index << ": " << cst.depth(v) << endl;
      leafTable[index] = i;
    }

  //test depth
  cout << "Test depth: "
       <<  cst.depth(cst.lca(cst.select_leaf(leafTable[0]),
			     cst.select_leaf(leafTable[8])));

  return 0;
}
