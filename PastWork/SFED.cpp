//
// Created by shelby on 11/16/2019
//	Completed code for Suffix Tree Edit Distance Algorithm
//

#include "SFED.h"
#include <string>
#include <vector>
#include <sdsl/suffix_trees.hpp>
using namespace std;
//using namespace sdsl;

typedef sdsl::cst_sct3<> cst_t;
//typedef sdsl::cst_sada<> csts_t;

SuffixTreeED::SuffixTreeED(string w1, string w2, int k)
: w1(w1), w2(w2), k(k)
{
    AxBy = w1 + "#" + w2 + "$";
}

int SuffixTreeED::computeED() {
    cst_t cst;
    sdsl::construct_im(cst, AxBy, 1);
    vector<Elem> prev((2 * k) + 1, {0, Elem::POSITION::none, 0, 0 });
    vector<Elem> curr((2 * k) + 1, {0, Elem::POSITION::none, 0, 0 });
    vector<int> leafTable(AxBy.length() + 1, 0);   //represents leaf number corresponding to index in string
    int temp;
    //fill table
    for(int i = 1; i <= AxBy.length() + 1; i++)
    {
        auto v = cst.select_leaf(i);
        int index = AxBy.length() - cst.depth(v) + 1;
        leafTable[index] = i;
    }

    //first diagonal
    /*temp = cst.depth(cst.lca(cst.select_leaf(leafTable[0]),
                             cst.select_leaf(leafTable[w1.length() + 1])));*/
    prev[k] = {0, Elem::POSITION::diagonal, cst.depth(cst.lca(cst.select_leaf(leafTable[0]),
                                                              cst.select_leaf(leafTable[w1.length() + 1]))), 0};

    //if words are the same
    if(w2.length() - w1.length() == 0 && prev[k].i == w1.length())
    {
        ED = prev[k];
        matrix.push_back(prev);
        return 0;
    }

    matrix.push_back(prev);

    //begin computing h waves
    for(int h = 1; h <= k; h++)
    {
        //each diagonal of h
        for(int d = -h; d <= h; d++)
        {
            int upper = 0, diagonal = 0, lower = 0;
            //slide
            //upper
            if(d < (h - 1))
            {
                upper = prev[d + k + 1].i + 1;
            }
            //current diagonal
            if((-h < d) && (d < h))
            {
                diagonal = prev[d + k].i + 1;
            }
            //lower diagonal
            if(d > (-h + 1))
            {
                lower = prev[d + k - 1].i;
            }
            //find highest value and write that to respective slot in curr
            if (upper > diagonal)
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
            }
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
    return -1;
};

void SuffixTreeED::optimalPath() {
    int a = ED.h;
    int b = ED.d + k;

    if(ED.h == 0)   //no edit distance, words are the same
    {
        cout << "\n(" << matrix[a][b].i << ", " << matrix[a][b].i + matrix[a][b].d << "), d: " << matrix[a][b].d << ", h: " << matrix[a][b].h << endl;
    }
    /*//check 2D vector
    for(vector<Elem> v: matrix)
    {
        cout << "\nh = " << v[k].h << ": ";
        for(Elem val: v)
        {
            cout << "( " << val.d << ", " << val.i << ")";
        }
    }*/
    while(matrix[a][b].h != 0)
    {
        cout << "\n(" << matrix[a][b].i << ", " << matrix[a][b].i + matrix[a][b].d << "), d: " << matrix[a][b].d << ", h: " << matrix[a][b].h << endl;
        switch(matrix[a][b].pos) {
            case Elem::POSITION::upper:
                for(Elem val : matrix[a - 1]) {
                    if(val.d == matrix[a][b].d + 1 && val.h == a - 1) {
                        a = val.h;
                        b = val.d + k;
                    }
                }
                break;
            case Elem::POSITION::diagonal:
                for(Elem val : matrix[a - 1]) {
                    if(val.d == matrix[a][b].d && val.h == a - 1) {
                        a = val.h;
                        b = val.d + k;
                        break;
                    }
                }
                break;
            case Elem::POSITION::lower:
                for(Elem val : matrix[a - 1]) {
                    if(val.d == matrix[a][b].d - 1 && val.h == a - 1) {
                        a = val.h;
                        b = val.d + k;
                        break;
                    }
                }
                break;
            case Elem::POSITION::none:
                throw invalid_argument("Position not logged correctly; referenced an unfilled cell.");
        }
        if(matrix[a][b].h == 0) {
            cout << "\n(" << matrix[a][b].i << ", " << matrix[a][b].i + matrix[a][b].d << "), d: " << matrix[a][b].d << ", h: " << matrix[a][b].h << endl;
            if(matrix[a][b].i + matrix[a][b].d == 0)
            {
                cout << "(1, 1), d: 0, h: " << matrix[a][b].h;
            }

        }
    }
}
