#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

#include "commonf.h"
#include "statistic.h"
#include "table.h"

// function prototype
vector<int> calcMarksRange(vector<double>);
int maxFreqOfRange(vector<int>);
int unitDistribution(vector<int>);
string unitSize (int);
vector<string> outputStar(vector<int>, int);
void plotHistogram(string, vector<string>, vector<int>, string, int);
void exportHistoTxt(string, string, vector<string>, vector<int>, string, int);

// output the freq of each range
vector<int> calcMarksRange(vector<double> marks){
	vector<int> count (10);

  for(double mark : marks){
    int tmp = mark/10;
    if(tmp == 10)
      tmp = 9;
    count[tmp]++;
  }

	return count;
}

// count the max freq of a range 
int maxFreqOfRange(vector<int> count){
	vector<double> tmp(count.begin(), count.end()); //cast int to double
  return maxVect(tmp);
}

// output the unit size  
// ltr can static_cast this function into int to get histogram size
int unitDistribution(vector<int> count){
  int n = maxFreqOfRange(count);
  if(n <= 20)
    return 1;
	return ceil(n / 20.0);
}

string unitSize (int n){
	if ( n == 1 )
		return "1 unit ";
	return to_string(n) + " units ";
}

// output histogram * in a vector<string> 
vector<string> outputStar(vector<int> count, int size){
	vector<string> star (10);

	for(int i = 0; i < 10; i++){
		star[i] = rjust(20, strRepeat("*", count[i]/size));
	}
	
	return star;
}

void plotHistogram(string title, vector<string> markRange, vector<int> freq, string starUnit, int n){
	vector<string> strStar = outputStar(freq, n);    // output histogram

	cout << "========== Histogram for " << title  << " ==========" << endl << endl;
	cout << "# Note that each (*) represents " << starUnit << endl << endl;

	PrintTableByVect(title, {}, {"Range", "Frequency"}, transposeV({markRange, strStar}));
}

// uses buffer to output text file
void exportHistoTxt(string fileName, string title, vector<string> markRange, vector<int> freq, string starUnit, int n){
  ofstream dataOut;
  dataOut.open(fileName);

  streambuf *psbuf, *backup;
  backup = cout.rdbuf();
  psbuf = dataOut.rdbuf();
  cout.rdbuf(psbuf);

  plotHistogram(title, markRange, freq, starUnit, n);

  cout.rdbuf(backup);

	dataOut.close();
}