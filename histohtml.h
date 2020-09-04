#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

#ifndef HISTOHTML_H_
#define HISTOHTML_H_

void cssHistogram(ofstream&);
vector<int> outputWidth(vector<int>, int);
vector<double> percentWidth(vector<int>, int);
void csshistoBar(vector<string>, vector<int>, vector<string>, int, ofstream&);
void divHistoBar(vector<string>, vector<string>, vector<int>, ofstream&);
void buildHistogram(string, vector<string>, vector<int>, vector<string>, int, string, ofstream&);
void histogramHTML(string, string, vector<string>, vector<int>, string, int);

#endif