#include <vector>
#include <fstream>
using namespace std;

#ifndef LOADFILE_H_
#define LOADFILE_H_

string loadFile(vector<string>&, vector<vector<double>>&);
string getFileName();
bool getColTitleRow(ifstream&, int&, vector<string>&, int&);
bool getTitleRow(ifstream&, vector<string>&);
bool getData(ifstream&, vector<vector<double>>&);
bool isColRowMatch(vector<vector<double>>, int, int);

#endif