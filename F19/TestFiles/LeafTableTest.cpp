#include <vector>
#include <sdsl/suffix_trees.hpp>

using namespace std;
using namespace sdsl;

typedef cst_sct3<> cst_t;
typedef cst_sada<> csts_t;

int main()
{
    /*//BY ID-
    string AxBy = "umulmundumulmum$";
    cst_t cst;
    construct_im(cst, AxBy, 1);
    vector<int> leafTable(AxBy.length());
    
    //fill table
    for(int i = 1; i <= AxBy.length() + 1; i++)
    {
        auto v = cst.select_leaf(i);
        int index = AxBy.length() - cst.depth(v) + 1;
	cout << "i = " << i << ", index = " << index << endl;
        leafTable[index] = cst.id(v);
    }
    
    //output table
    cout << "Table Index\tString\n";
    for(int i = 0; i < AxBy.length(); i++)
    {
        cout << i << "\t\t" << extract(cst, cst.inv_id(leafTable[i])) << endl;
    }
    **************************/
	string AxBy = "umulmundumulmum$";
    cst_t cst;
    construct_im(cst, AxBy, 1);
    vector<int> leafIndex(AxBy.length());
    //fill table
    for(int i = 1; i <= AxBy.length() + 1; i++)
    {
        auto v = cst.select_leaf(i);
        int index = AxBy.length() - cst.depth(v) + 1;
    	cout << "i = " << i << ", index = " << index << endl;
        leafIndex[index] = i;
    }

    
    //output table
    cout << "Table Index\tString\n";
    for(int i = 0; i < AxBy.length(); i++)
    {
	auto v = cst.select_leaf(leafIndex[i]);
        cout << i << "\t\t" << extract(cst, v) << endl;
    }

}
