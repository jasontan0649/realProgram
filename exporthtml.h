#include <vector>
#include <fstream>
#include <string>
using namespace std;

#ifndef EXPORTHTML_H_
#define EXPORTHTML_H_

//function to export HTML
void exportHTML(string, string, vector<string>, vector<string>, vector<vector<double>>, string mode = "once");
void titleHTML(string, ofstream&);
void tableHTML(vector<string>, vector<string>, vector<vector<double>>, ofstream&);
void thTable(vector<string>, ofstream&);
void tdTable(vector<vector<double>>, vector<string>, ofstream&);


#endif