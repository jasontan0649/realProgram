#include <vector>
using namespace std;

#ifndef histoLRAndPearson_H_
#define histoLRAndPearson_H_

//Export into HTML File
void exportPCLRHtml(string, string, vector<string>, vector<string>, vector<vector<string>> ,vector<double>,vector<double>,double,double,double,string mode = "once");
void PCHtml(vector<double>,vector<double>,double,ofstream&);
void LRHtml(vector<double>,vector<double>,double,double,double,ofstream&);

#endif