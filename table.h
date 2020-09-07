#include <vector>
#include <fstream>
using namespace std;

#ifndef TABLE_H_
#define TABLE_H_

//algorithm to generate table
vector<vector<string>> convertDVectToSVect(vector<vector<double>>);
int findMaxInVect(vector<string>);
double findMaxBetweenTwoNums(int, double);
string joinVect(vector<string>, string);
vector<int> getColMaxLength(vector<string>, vector<vector<string>>);
vector<string> getHeader(vector<string>, bool, vector<int>, int);
string getBorder(vector<string>);



//function to export txt
void exportTxt(string, string, vector<string>, vector<string>, vector<vector<double>>, string mode = "new");
void exportTxt(string, string, vector<string>, vector<string>, vector<vector<string>>, string mode = "new");


//function to display Table
void PrintTableByVect(string, vector<string>, vector<string>, vector<vector<double>>);
void PrintTableByVect(string, vector<string>, vector<string>, vector<vector<string>>);

void printHeader(string, string);
void printTableData(bool, int, vector<string>, vector<int>, vector<vector<string>>, string);

#endif