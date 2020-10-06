#include <vector>
using namespace std;

#ifndef LRAndPearson_H_
#define LRAndPearson_H_

vector<double> sqVect(vector<double>);
vector<double> productXY(vector<double>,vector<double>);
double pearsonCorr(vector<double>,vector<double>);
double slope(double,vector<double>,vector<double>);
double y_Intercept(double,vector<double>,vector<double>);
string linearRegression(vector<double>,vector<double>,double,double,double);

//Display Calculation On console
void printComputationOfPC(vector<double>,vector<double>, double);
void printComputationOfLR(vector<double>,vector<double>,double,double,double);

//Export into txt file
void exportPCLRTxt(string,string,vector<string>,vector<string>,vector<vector<string>>,vector<double>,vector<double>,double,double,double);

#endif