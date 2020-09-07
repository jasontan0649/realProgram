#include <vector>
using namespace std;

#ifndef LRAndPearson_H_
#define LRAndPearson_H_

vector<double> sqVect(vector<double>);
vector<double> productXY(vector<double>,vector<double>);
double pearsonCorr(vector<double>,vector<double>);
double slope(double,vector<double>,vector<double>);
double y_Intercept(double,vector<double>,vector<double>);
string linearRegression(vector<double>,vector<double>);
#endif