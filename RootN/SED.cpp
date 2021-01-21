//
// created by shelby on 21 October 2020
//	suffix tree edit distance class
//

#include <vector>
#include "SED.h"
#include "Elem.h"

using namespace std;
using namespace sdsl;

typedef cst_sct3<csa_wt<wt_int<rrr_vector<>>>> cst_t;

//
// Constructor only takes concatenated strings
//
SED::SED(int_vector<> AxBy, int k)
  : AxBy(AxBy), k(k)
{}


int SED::computeED() {
  cst_t cst;
  construct_im(cst, AxBy);
  vector<Elem> prev((2 * k) + 1, {0, Elem::POSITION::none, 0, 0});
  vector<Elem> curr((2 * k) + 1, {0, Elem::POSITION::none, 0, 0});
  //table of leaf numbers corresponding to index in string
  vector<int> leafTable(AxBy.size() + 1, 0);
  int tmp;	//for debugging???

  //fill table
  for(int i = 1; i <= AxBy.size() + 1; i++)
    {
      auto v = cst.select_leaf(i);
      int index = AxBy.length() - cst.depth(v) + 1;
      leafTable[index] = i;
    }

  //first diagonal
  prev[k] = {0, Elem::POSITION::diagonal, cst.depth(cst.lca(cst.select_leaf(leafTable[0]),
							    cst.select_leaf(leafTable[lengthA + 1]))), 0};

  //if strings are the same
  if(lengthB - lengthA == 0 && prev[k].i == lengthA)
    {
      ED = prev[k];
      matrix.push_back(prev);
      return 0;
    }

  matrix.push_back(prev);

  // begin computing h waves
  for(int h = 1; h <= k; h++)
    {
      // each diagonal of h
      for(int d = -h; d <= h; d++)
	{
	  int upper = 0,
	    diagonal = 0,
	    lower = 0;
	  //slide
	  	// upper diagonal
	  if(d < (h - 1))
	    upper = prev[d + k + 1].i + 1;
	  	// current diagonal
	  if((-h < d) && (d < h))
	    diagonal = prev[d + k].i + 1;
	 	// lower diagonal
	  if(d > (-h + 1))
	    lower = prev[d + k - 1].i;
	  //find highest value and write that to respective slot in curr
	  if(upper > diagonal)
	    {
	      if (upper > lower)  //upper is max value
		{
		  temp = upper + cst.depth(cst.lca(cst.select_leaf(leafTable[upper]),
						   cst.select_leaf(leafTable[w1.length() + 1 + upper + d])));
		  curr[d + k] = {h, Elem::POSITION::upper, temp, d};
		}
	      else                //lower is max value
		{
		  temp = lower + cst.depth(cst.lca(cst.select_leaf(leafTable[lower]),
						   cst.select_leaf(leafTable[w1.length() + 1 + lower + d])));
		  curr[d + k] = {h, Elem::POSITION::lower, temp, d};
		}
	    }
	  else
	    {
	      if(diagonal > lower)//diagonal is max value
		{
		  temp = diagonal + cst.depth(cst.lca(cst.select_leaf(leafTable[diagonal]),
						      cst.select_leaf(leafTable[w1.length() + 1 + diagonal + d])));
		  curr[d + k] = {h, Elem::POSITION::diagonal, temp, d};
		}
	      else                //lower is max value
		{
		  temp = lower + cst.depth(cst.lca(cst.select_leaf(leafTable[lower]),
						   cst.select_leaf(leafTable[w1.length() + 1 + lower + d])));
		  curr[d + k] = {h, Elem::POSITION::lower, temp, d};
		}
	    }//end outer else

	  //check bound
	  if (d == w2.length() - w1.length() && (curr[d + k].i == w1.length()))
	    {
	      ED = curr[d + k];
	      matrix.push_back(curr); //push back what we have of curr
	      return h;
	    }
	}

      matrix.push_back(curr);

      //update prev
      for(int i = 0; i < 2 * k; i++)
	{
	  prev[i] = curr[i];
	}
    }
  //otherwise return 0
  return 0;
}

/*vector<int> SED::optimalPath()
{
  //return empty for now
  vector<int> tmp;
  return tmp;
  }*/
