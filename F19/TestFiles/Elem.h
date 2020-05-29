//
// Created by shelby on 12/14/19.
//

#ifndef MAIN_CPP_ELEM_H
#define MAIN_CPP_ELEM_H

struct Elem
{
    int h;      //edit distance
    enum POSITION {none, upper, diagonal, lower} pos; //position that it was calculated from
    int i;      //row
    int d;      //diagonal
};

#endif //MAIN_CPP_ELEM_H
