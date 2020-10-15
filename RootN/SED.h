//
//	made by shelby on 2 October 2020
//		header file for string edit distance class
//

#ifndef _SED_H_
#define _SED_H_

class SED
{
 private:
  int k;		//guess value
  vector<int> A;	//first string
  vector<int> B;	//second string
  vector<int> AxBy;	//concatenated strings
  vector<vector<Elem>> matrix;
  Elem ED;		//edit distance

 public:
  //constructor
  SED(vector<int> A, vector<int> B, int k);

  //to compute edit distance
  
};

#endif //_SED_H_
