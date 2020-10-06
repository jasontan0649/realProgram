#include <vector>
using namespace std;

#ifndef LRAndPearsonHtml_H_
#define LRAndPearsonHtml_H_

//Export into HTML File
void exportPCLRHtml(string, string, vector<string>, vector<string>, vector<vector<string>> ,vector<double>,vector<double>,double,double,double);
void PCHtml(vector<double>,vector<double>,double,ofstream&);
void LRHtml(vector<double>,vector<double>,double,double,double,ofstream&);

#endif