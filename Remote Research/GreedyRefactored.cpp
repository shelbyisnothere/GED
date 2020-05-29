//
// Created by shelby on 1/31/20.
//

#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include <vector>
#include "Cell.h"
#include "GreedyRefactored.h"

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;

using namespace std;

GreedyRefactored::GreedyRefactored(vector<Cell> curve1, vector<Cell> curve2, int k)
: curve1(curve1), curve2(curve2), k(k)
{}

int GreedyRefactored::computeED()
{
    vector<Elem> prev((2 * k) + 1, {-1, Elem::POSITION::none, -1, -1});
    vector<Elem> curr((2 * k) + 1, {-1, Elem::POSITION::none, -1, -1});

    //first diagonal
    prev[k] = {0, Elem::POSITION::diagonal, slide(0, 0), 0};

    //if words are the same
    if(curve2.size() - curve1.size() == 0 && prev[k].i == curve1.size() + 1)
    {
        ED = prev[k];
        matrix.push_back(prev);
        return 0;
    }

    matrix.push_back(prev);

    //begin computing h waves
    for(int h = 1; h <= k; h++)
    {
        cout << "\nh = " << h << ": ";
        //each diagonal of h
        for(int d = -h; d <= h; d++)
        {
            /*//SUBSTITUTIONS ALLOWED:
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
                else //if (diagonal < lower)//lower is max value
                {
                    curr[d + k] = {h, Elem::POSITION::lower, slide(lower, lower + d), d};
                }
            }*/

            //SUBSTITUTIONS DISALLOWED:
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
                curr[d + k] = {h, Elem::POSITION::upper, slide(upper - 1, upper + d - 1), d};
                cout << " (" << curr[d + k].i << ", " << curr[d + k].i + curr[d+k].d << ") ";
            }
            else                //lower is max value
            {
                curr[d + k] = {h, Elem::POSITION::lower, slide(lower - 1, lower + d - 1), d};
                cout << " (" << curr[d + k].i << ", " << curr[d + k].i + curr[d+k].d << ") ";
            }

            //check bound
            if (d == curve2.size() - curve1.size() && (curr[d + k].i == curve1.size()))
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
            curr[i] = {-1, Elem::POSITION::none, -1, -1};
        }
    }
    return -1;
}

vector<Point_2> GreedyRefactored::getAlignment()
{
    vector<Point_2> alignment;

    if(ED.h == -1)
    {
        return alignment;
    }

    int a = ED.h;
    int b = ED.d + k;

    if(ED.h == 0)   //no edit distance, words are the same
    {
        //cout << "\n(" << slideVals[a][b].i << ", " << slideVals[a][b].i + slideVals[a][b].d << "), d: " << slideVals[a][b].d << ", h: " << slideVals[a][b].h << endl;
        for(int i = ED.i; i >= 0; i--)
        {
            Point_2 p(i, i);
            alignment.push_back(p);
        }
    }

    while(matrix[a][b].h != 0)
    {
        //cout << "\n(" << slideVals[a][b].i << ", " << slideVals[a][b].i + slideVals[a][b].d << "), d: " << slideVals[a][b].d << ", h: " << slideVals[a][b].h << endl;


        switch(matrix[a][b].pos) {
            case Elem::POSITION::upper:
                for(Elem val : matrix[a - 1]) {
                    if(val.d == matrix[a][b].d + 1 && val.h == a - 1) {
                        int x = matrix[a][b].i;
                        int y = matrix[a][b].i + matrix[a][b].d;
                        for(int i = matrix[a][b].i; i > val.i; i--)
                        {
                            Point_2 p(x, y);
                            alignment.push_back(p);
                            x--;
                            y--;
                        }

                        //switch slides
                        a = val.h;
                        b = val.d + k;
                    }
                }
                break;
            case Elem::POSITION::diagonal:
                for(Elem val : matrix[a - 1]) {
                    if(val.d == matrix[a][b].d && val.h == a - 1) {
                        int x = matrix[a][b].i;
                        int y = matrix[a][b].i + matrix[a][b].d;
                        for(int i = matrix[a][b].i; i > val.i; i--)
                        {
                            Point_2 p(x, y);
                            alignment.push_back(p);
                            x--;
                            y--;
                        }

                        a = val.h;
                        b = val.d + k;
                        //break;
                    }
                }
                break;
            case Elem::POSITION::lower:
                for(Elem val : matrix[a - 1]) {
                    if(val.d == matrix[a][b].d - 1 && val.h == a - 1) {
                        int x = matrix[a][b].i;
                        int y = matrix[a][b].i + matrix[a][b].d;
                        for(int i = matrix[a][b].i; i >= val.i; i--)
                        {
                            Point_2 p(x, y);
                            alignment.push_back(p);
                            x--;
                            y--;
                        }

                        a = val.h;
                        b = val.d + k;
                        //break;
                    }
                }
                break;
            case Elem::POSITION::none:
                throw invalid_argument("Position not logged correctly; referenced an unfilled cell.");
        }
        if(matrix[a][b].h == 0) {
            int x = matrix[a][b].i;
            int y = matrix[a][b].i + matrix[a][b].d;
            for(int i = matrix[a][b].i; i >= 0; i--)
            {
                Point_2 p(x, y);
                alignment.push_back(p);
                x--;
                y--;
            }
            //cout << "\n(" << slideVals[a][b].i << ", " << slideVals[a][b].i + slideVals[a][b].d << "), d: " << slideVals[a][b].d << ", h: " << slideVals[a][b].h << endl;

        }
    }

    reverse(alignment.begin(), alignment.end());
    return alignment;

}

//slide takes the INDEXES of the cell being slid from and returns the ROW NUMBER ACCORDING TO MATRIX
int GreedyRefactored::slide(int i, int j) {
    for(int a = 0; a < curve1.size() || a < curve2.size(); a++)
    {
        if(curve1[i + 1].hor == curve2[j + 1].hor && curve1[i + 1].vert == curve2[j + 1].vert)
        {
            i++;
            j++;
        }
        else if (i == 0 && j == 0) //first points aren't same
        {
            return i;
        }
        else
        {
            return i + 1;
        }
    }
    return i + 1;   //curve of size 0 or end of matrix has been reached
}
