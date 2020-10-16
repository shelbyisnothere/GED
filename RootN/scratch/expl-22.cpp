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
  int_vector<> vec(0);
  int_vector<> tmp(3);
  tmp[0] = 1;
  tmp[1] =2;
  tmp[2] = 4;
  vec = push(vec, 1);
  for(size_t i = 0; i < vec.size(); i++)
    {
      cout << vec[i] << " ";
    }
  return 0;
}
