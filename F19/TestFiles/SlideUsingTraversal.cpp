#include <string>
#include "DPED.h"
#include "GreedyED.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <sdsl/suffix_trees.hpp>
//using namespace std::chrono;
using namespace std;
using namespace sdsl;

typedef cst_sct3<> cst_t;
typedef cst_sada<> csts_t;

int slide(cst_t cst, int i, int j);

int main()
{
    string w1 = "ATGGTATA";
    string w2 = "AGGATATTA";
    int k = 15;

    DPED testDP(w1, w2);
    GreedyED testGreedy(w1, w2, k);
    cout << "DYNAMIC PROGRAMMING ALG: \n";
    auto start = std::chrono::high_resolution_clock::now();
    cout << testDP.computeED() << endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Time: " << duration.count() << " microseconds";

    cout << endl << endl;
    cout << "GREEDY ALG: \n";
    start = std::chrono::high_resolution_clock::now();
    cout << testGreedy.computeED() << endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Time: " << duration.count() << " microseconds";

    cout << endl << endl;
    cout << "SUFFIX TREE ALG: [being tested] \n";
    string AxBy = w1 + "#" + w2 + "#";
    cst_t cst;
    construct_im(cst, "ATGGTATA#AGGATATTA$", 1);
    vector<int> prev((2 * k) + 1, 0);
    vector<int> curr((2 * k) + 1, 0);
	int d;			//depth
	int index, uID, wID;
	uint64_t max_depth = AxBy.length() + 1;

	/*//traverse tree to find leaves
	for (auto it=cst.begin(); it!=cst.end(); ++it) {
        if (it.visit() == 1) {  // node visited the first time
            auto v = *it;       // get the node by dereferencing the iterator
            if (cst.depth(v) <= max_depth) {   // if depth node is <= max_depth
		if(cst.is_leaf(v)) {		
			index = AxBy.length() - extract(cst, v).length() + 1;
				if(index == 0) {
					uID = cst.id(v);
					cout << "\nu: " << extract(cst, v) << endl;
				}
				else if(index == w1.length() + 1) {
					wID = cst.id(v);
					cout << "\nw: " << extract(cst, v) << endl;
				}
		}
	    }else { // skip the subtree otherwise
                it.skip_subtree();
            }
        }
        }
    //first diagonal
	try 
	{
		auto lca = cst.lca(cst.inv_id(uID), cst.inv_id(wID));
		d = cst.depth(lca);
		//cout << endl << extract(cst, lca) << endl;
	}
	catch(exception& e)
	{
		cout << "\nERROR\n";
		d = -1;
	}*/

    prev[k] = slide(cst, 0 , w1.length() + 1);
    for(int i = 0; i <= 2 * k; i++)
    {
        cout << prev[i] << " ";
    }

	/*//begin computing h waves
	for(int h = 1; h <= k; h++) {
		//each diagonal of h
		for(int d = -h; d <= h; d++) {
			
		}
	}*/
	
    cout << endl;
}

int slide(cst_t cst, int i, int j) {
//traverse tree to find leaves
	uint64_t max_depth = extract(cst.csa, 0, cst.csa.size()-1).length() + 1;
	int uID, wID, index;
	for (auto it=cst.begin(); it!=cst.end(); ++it) {
	        if (it.visit() == 1) {  // node visited the first time
	            auto v = *it;       // get the node by dereferencing the iterator
	            if (cst.depth(v) <= max_depth) {   // if depth node is <= max_depth
			if(cst.is_leaf(v)) {		
				index = extract(cst.csa, 0, cst.csa.size()-1).length() - extract(cst, v).length();
					if(index == i) {
						uID = cst.id(v);
						cout << "\nu: " << extract(cst, v) << endl;
					}
					else if(index == j) {
						wID = cst.id(v);
						cout << "\nw: " << extract(cst, v) << endl;
					}
			}
		    }else { // skip the subtree otherwise
	                it.skip_subtree();
	            }
        }
        }
	auto lca = cst.lca(cst.inv_id(uID), cst.inv_id(wID));
	return cst.depth(lca);	
}