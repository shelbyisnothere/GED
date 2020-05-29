//
// Created by shelby on 10/28/19.
//

#include "GreedyED.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

GreedyED::GreedyED(string w1, string w2, int k)
: w1("#" + w1), w2("#" + w2), k(k)
{}

int GreedyED::computeED() {
    //bool edFound = false;
    vector<Elem> prev((2 * k) + 1, {0, Elem::POSITION::none, 0, 0 });
    vector<Elem> curr((2 * k) + 1, {0, Elem::POSITION::none, 0, 0 });
    //int d = 0; //diagonal

    //first diagonal
    prev[k] = {0, Elem::POSITION::diagonal, slide(0, 0), 0};

    //if words are the same
    if(w2.length() - w1.length() == 0 && prev[k].i == w1.length() - 1)
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
            //SUBSTITUTIONS ALLOWED:
            int upper = 0, diagonal = 0, lower = 0;
            //slide
            //upper diagonal
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
                    curr[d + k] = {h, Elem::POSITION::upper, slide(upper, upper + d), d};
                }
                else                //lower is max value
                {
                    curr[d + k] = {h, Elem::POSITION::lower, slide(lower, lower + d), d};
                }
            }
            else
            {
                if(diagonal > lower)//diagonal is max value
                {
                    curr[d + k] = {h, Elem::POSITION::diagonal, slide(diagonal, diagonal + d), d};
                }
                else if (diagonal < lower)//lower is max value
                {
                    curr[d + k] = {h, Elem::POSITION::lower, slide(lower, lower + d), d};
                }
            }

            /*//SUBSTITUTIONS DISALLOWED:
            int upper = 0, lower = 0;
            //slide
            //upper diagonal
            if(d < (h - 1))
            {
                upper = prev[d + k + 1].i + 1;
            }

            if(d > (-h + 1))
            {
                lower = prev[d + k - 1].i;
            }

            if (upper > lower)  //upper is max value
            {
                curr[d + k] = {h, Elem::POSITION::upper, slide(upper, upper + d), d};
            }
            else                //lower is max value
            {
                curr[d + k] = {h, Elem::POSITION::lower, slide(lower, lower + d), d};
            }*/

            //check bound
            if (d == w2.length() - w1.length() && (curr[d + k].i == w1.length() - 1))
            {
                ED = curr[d + k];
                matrix.push_back(curr); //push back what we have of curr
                return h;
            }
        }

        matrix.push_back(curr);

        //update prev, empty curr
        for(int i = 0; i < 2 * k; i++)
        {
            prev[i] = curr[i];
            curr[i] = {0, Elem::POSITION::none, 0, 0 };
        }
    }
    return -1;
}

int GreedyED::slide(int i, int j) {
    do
    {
        if(w1[i + 1] == w2[j + 1])
        {
            i++;
            j++;
        }
        else
        {
            return i;
        }
    } while(w1[i + 1] != 0 || w2[j + 1] != 0);
    return i;
}

void GreedyED::optimalPath() {
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

        }
    }
}

