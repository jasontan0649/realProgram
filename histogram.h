#include <string>
#include <vector>
using namespace std;

#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

vector<int> calcMarksRange(vector<double>);
int maxFreqOfRange(vector<int>);
int unitDistribution(vector<int>);
string unitSize (int);
vector<string> outputStar(vector<int>, int);
void plotHistogram(string, vector<string>, vector<int>, string, int);

#endif