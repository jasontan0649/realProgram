#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

bool isNum(string);
double round(double, int pre = 0);

string strRepeat(string, int);
string toStr(double, int pre=-1); //custom build to string function
string spaceNeeded(int);
string center(int, string);
string ljust(int, string);
string rjust(int, string);

//finf max size(length) in vector
int findMaxInVect(vector<string>);

//vector double to string
vector<string> vectDoubleString(vector<double>);

//transpose vector
vector<vector<double>> transposeV(vector<vector<double>>);
vector<vector<string>> transposeV(vector<vector<string>>);

//sort by column
void sortByCol(vector<vector<double>>&, int);
void sortByRow(vector<vector<double>>&, int);

//system function
void clrScr();

//common function
//to check is a number
bool isNum(string s) {
	int d = 0; //dot count
	
  for (char c : s) //iterate through char of s, return false if not digit or dot
		if ( (!isdigit(c) && c != '.') || (c=='.' && ++d > 1) )
			return false;

	return true; //check completed
}

double round(double val, int pre){
  int tmp = (val * pow(10,pre) + 0.5); // get value of ceiling of val*10^pre
  return double(tmp) / pow(10,pre); //return the rounded value base on precision
}

string strRepeat(string s, int n) {
	string res = ""; //create empty string

	for (int i = 0; i < n; i++) //concatenate string n times
		res += s;

	return res; //return string
}

string toStr(double val, int pre) { //number to string
  if(pre!=-1) //if not default para, round the value
    val = round(val, pre);

  string str = to_string(val); //convert to string
  str.erase(str.find_last_not_of('0') + 1); //remove trailing 0

  if (str.back() == '.') //remove . if whole number
    str.pop_back();

	return str; //return string val
}

string spaceNeeded(int val) {
	return strRepeat(" ", val); //repeat space val times
}

string center(int val, string str) {
	int spaceAllowed = val - str.size();
	double pad = spaceAllowed / 2.0;
	double leftPad, rightPad;

	leftPad = floor(pad);
	rightPad = ceil(pad);

	return spaceNeeded(leftPad) + str + spaceNeeded(rightPad);
}

string ljust(int val, string str) {
	int spaceAllowed = val - str.size();
	return spaceNeeded(spaceAllowed) + str;
}

string rjust(int val, string str) {
	int spaceAllowed = val - str.size();
	return str + spaceNeeded(spaceAllowed);
}

//Max Function
int findMaxInVect(vector<string> arr) {
	int res = arr[0].size();
	for (int i = 1; i < arr.size(); i++)
		if (arr[i].size() > res)
			res = arr[i].size();

	return res;
}

vector<string> vectDoubleString(vector<double> data) {
	const int size = data.size();
  vector<string> res (size);

	for (int i = 0; i < size; i++) 
    res[i] = toStr(data[i]);

	return res;
}


//tranpose vector
vector<vector<double>> transposeV(vector<vector<double>> vect) {
  vector<vector<double>> res;
	const int row = vect.size();
	const int col = vect[0].size();

	res.resize(col, vector<double>(row));

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			res[j][i] = vect[i][j];
		}
	}

  return res;
}

// overloading for string // 
vector<vector<string>> transposeV(vector<vector<string>> vect) {
  vector<vector<string>> res;
	const int row = vect.size();
	const int col = vect[0].size();

	res.resize(col, vector<string>(row));

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			res[j][i] = vect[i][j];
		}
	}

  return res;
}

//Sort By Columns
void sortByCol(vector<vector<double>>& arr, int n) {
	const int size = arr.size();
	vector<double> tmp;

	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (arr[j][n] > arr[j + 1][n]) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}

}

void sortByRow(vector<vector<double>>& arr, int n){
  arr = transposeV(arr);
  sortByCol(arr, n);
  arr = transposeV(arr);
}

//System Fucntione
void clrScr() {
	system("cls||clear");
	//support posix and windows
}