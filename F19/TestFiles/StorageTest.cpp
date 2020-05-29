//
// Created by shelby on 12/14/19.
//

#include <string>
#include <vector>
#include <sdsl/suffix_trees.hpp>
#include "Elem.h"
using namespace std;
//using namespace sdsl;

typedef sdsl::cst_sct3<> cst_t;
//typedef sdsl::cst_sada<> csts_t;

int main() {
    cst_t cst;
    string w1 = "TEST";
    string w2 = "TESTT";
    int s = 0;
    string AxBy = w1 + "#" + w2 + "$";
    int k = 10;
    sdsl::construct_im(cst, AxBy, 1);
    vector <Elem> prev((2 * k) + 1, {0, Elem::POSITION::none, 0, 0});
    vector <Elem> curr((2 * k) + 1, {0, Elem::POSITION::none, 0, 0});
    vector<int> leafTable(AxBy.length() + 1, 0);   //represents leaf number corresponding to index in string
    int temp;
    //fill table
    for (int i = 1; i <= AxBy.length() + 1; i++) {
        auto v = cst.select_leaf(i);
        int index = AxBy.length() - cst.depth(v) + 1;
        leafTable[index] = i;
    }

    for (int val: leafTable) {
        cout << "i = " << s << ", val = " << val;
        cout <<  ", depth = " << cst.depth(cst.select_leaf(val)) << endl;
        /*if(val != 1)
        {

        }*/
        s++;
    }

    temp = cst.depth(cst.lca(cst.select_leaf(leafTable[0]),
                             cst.select_leaf(leafTable[w1.length()])));
    cout << temp << endl;
    //prev[k] = {0, Elem::POSITION::diagonal, temp, 0};
}

