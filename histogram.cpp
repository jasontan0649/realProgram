#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

#include "commonf.h"
#include "statistic.h"
#include "table.h"

// output the freq of each range
vector<int> calcMarksRange(vector<double> marks){
	vector<int> count (10);

	for (int i = 0; i < 100; i += 10){
		for (int j = 0; j < marks.size(); j++){
			if (marks[j] >= i && marks[j] < (i + 10) ){
				count[(i/10)] ++;
				marks[j] = {};
			} else if (marks[j] == 100){
				count[9] ++;
				marks[j] = {};
			}
		}
	}

	return count;
}

// count the max freq of a range 
int maxFreqOfRange(vector<int> count){
	vector<double> tmp(count.begin(), count.end());
	double i = maxVect(tmp);

	return static_cast<int> (i);
}

// output the unit size  
// ltr can static_cast this function into int to get histogram size
int unitDistribution(vector<int> count){
	int n = maxFreqOfRange(count);
	int i = 2;
	
	if (n <= 20)
		return 1;
	else{
		while(i*20 < n)
			i++;
		return i;
	}
}

string unitSize (int n){
	if ( n == 1 )
		return "1 unit ";
	else 
		return to_string(n) + " units ";
}

// output histogram * in a vector<string> 
vector<string> outputStar(vector<int> count, int size){
	vector<string> star (10);

	for(int i = 0; i < 10; i++){
		star[i] = rjust(20, strRepeat("*",count[i]/size));
	}
	
	return star;
}

void plotHistogram(string title, vector<string> markRange, vector<int> freq, string starUnit, int n){
	vector<string> strStar = outputStar(freq, n);    // output histogram

	cout << "========== Histogram for " << title  << " ==========" << endl << endl;
	cout << "# Note that each (*) represents " << starUnit << endl << endl;

	PrintTableByVect(title, {}, {"Range", "Frequency"}, transposeV({markRange, strStar}));
}