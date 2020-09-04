#include <vector>
#include <fstream>
using namespace std;

#ifndef STATISTIC_H_
#define STATISTIC_H_

double minVect(vector<double>);
double maxVect(vector<double>);
double median(vector<double>);
double mean(vector<double>);
double variance(vector<double>);
double sd(vector<double>);

double sum(vector<double>);
void sort(vector<double>&);

#endif