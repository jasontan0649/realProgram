#include <vector>
using namespace std;

//Header file
#ifndef COMMONF_H_
#define COMMONF_H_

bool isNum(string);
double round(double, int);

string strRepeat(string, int);
string toStr(double, int pre=-1); //custom build to string function
string spaceNeeded(int);
string center(int, string);
string ljust(int, string);
string rjust(int, string);

//finf max size(length) in vector
int findMaxInVect(vector<string>);

//vector double to string
vector<string> vectDoubleString(vector<double>);

//transpose vector
vector<vector<double>> transposeV(vector<vector<double>>);
vector<vector<string>> transposeV(vector<vector<string>>);

//sort by column
void sortByCol(vector<vector<double>>&, int);
void sortByRow(vector<vector<double>>&, int);

//system function
void clrScr();

#endif