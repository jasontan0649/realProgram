#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "commonf.h"
using namespace std;

//algorithm to generate table
vector<vector<string>> convertDVectToSVect(vector<vector<double>>);
double findMaxBetweenTwoNums(int, double);
string joinVect(vector<string>, string);
vector<int> getColMaxLength(vector<string>, vector<vector<string>>);
vector<string> getHeader(vector<string>, bool, vector<int>, int);
string getBorder(vector<string>);


//function to export txt
void exportTxt(string, string, vector<string>, vector<string>, vector<vector<double>>, string mode="new");
void exportTxt(string, string, vector<string>, vector<string>, vector<vector<string>>, string mode="new");
void printHeader(ofstream&, string, string);
void printTableData(ofstream&, bool, int, vector<string>, vector<int>, vector<vector<string>>, string);

//function to display Table
void PrintTableByVect(string, vector<string>, vector<string>, vector<vector<double>>);
void PrintTableByVect(string, vector<string>, vector<string>, vector<vector<string>>);
void printHeader(string, string);
void printTableData(bool, int, vector<string>, vector<int>, vector<vector<string>>, string);

//convert DoubleVect To StringVect 
vector<vector<string>> convertDVectToSVect(vector<vector<double>> data) {
	const int row = data.size();
	const int col = data[0].size();
	vector<vector<string>> res;
	res.resize(row, vector<string>(col));
	//res[row][col]
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			res[i][j] = toStr(data[i][j]);
		}
	}

	return res;
}

double findMaxBetweenTwoNums(int a, double b) {
	int large = a;
	if (b > a)
		large = b;

	return large;
}
//****************************************

//Export Txt and Display Data//
//Join vector string by delimiters
string joinVect(vector<string> vect, string delimiters) {
	string newStr = "";

	for (int i = 0; i < vect.size() - 1; i++) {
		newStr += vect[i] + delimiters;
	}

	newStr += vect[vect.size() - 1];

	return newStr;
}

vector<int> getColMaxLength(vector<string> colNames, vector<vector<string>> strData) {
	vector<int> colMaxLen;
	for (int i = 0; i < colNames.size(); i++) {
		colMaxLen.push_back(colNames[i].size());
	}
	for (int i = 0; i < strData.size(); i++) {
		for (int j = 0; j < strData[i].size(); j++) {
			colMaxLen[j] = findMaxBetweenTwoNums(colMaxLen[j], (strData[i][j]).size());
		}
	}

	return colMaxLen;
}

vector<string> getHeader(vector<string> colNames, bool noRowNames, vector<int> colMaxLen, int rowMaxLen) {

	vector<string> tableStart;
	vector<string> colNameStart;

	if (noRowNames) {
		tableStart = {};
	}
	else {
		tableStart = { strRepeat(" ", rowMaxLen) };
	}

	for (int i = 0; i < colNames.size(); i++) {
		string colNamesCenterJustified = center(colMaxLen[i], colNames[i]);
		colNameStart.push_back(colNamesCenterJustified);
	}

	//Concatenate two vector string
	vector<string> header(tableStart);
	header.insert(header.end(), colNameStart.begin(), colNameStart.end());

	return header;
}

string getBorder(vector<string> header) {

	vector<int> headerNameLength;
	for (int i = 0; i < header.size(); i++) {
		headerNameLength.push_back(header[i].size());
	}

	vector<string> colBorder;
	for (int i = 0; i < headerNameLength.size(); i++) {
		colBorder.push_back(strRepeat("-", headerNameLength[i]));
	}

	//Join colBorder by "-+-"
	return joinVect(colBorder, "-+-");
}
//function to export txt

void exportTxt(string fileName, string title, vector<string> rowNames, vector<string> colNames, vector<vector<double>> data, string mode) {
  vector<vector<string>> strData = convertDVectToSVect(data);
  exportTxt(fileName, title, rowNames, colNames, strData, mode);
}

void exportTxt(string fileName, string title, vector<string> rowNames, vector<string> colNames, vector<vector<string>> strData, string mode) {

	vector<int> colMaxLen;
	bool noRowNames = rowNames.size() == 0;
	//Find the maximum length for row names
	int rowMaxLen = 0;
	if (!noRowNames)
		rowMaxLen = findMaxInVect(rowNames);
	//Find the maximum length for columns
	colMaxLen = getColMaxLength(colNames, strData);
	//Create header string with colNames
	vector<string> header = getHeader(colNames, noRowNames, colMaxLen, rowMaxLen);

	//Join vector string element by " | "
	string strHeader = joinVect(header, " | ");
	//Create Border
	string border = getBorder(header);

	ofstream dataOut;
  if(mode=="new")
	  dataOut.open(fileName);
  else
    dataOut.open(fileName, ios_base::app);
  
	dataOut << title << endl << endl;
	printHeader(dataOut, strHeader, border);
	printTableData(dataOut, noRowNames, rowMaxLen, rowNames, colMaxLen, strData, border);
	dataOut.close();
}

void printHeader(ofstream& dataOut, string strHeader, string border) {

	dataOut << "+-" << border << "-+" << endl;
	dataOut << "| " << strHeader << " |" << endl;
	dataOut << "+-" << border << "-+" << endl;

}

void printTableData(ofstream& dataOut, bool noRowNames, int rowMaxLen, vector<string>rowNames, vector<int> colMaxLen, vector<vector<string>> strData, string border) {
	//Show all rows of data
	string finalRowStr, colStrJustified;
	for (int row = 0; row < strData.size(); row++) {
		//Create row string AND Add row name as the first element in rowStr
		vector<string> rowStr;
		if (noRowNames) {
			rowStr = {};
		}
		else {
			string rowNamesRightJustified = rjust(rowMaxLen, rowNames[row]);
			rowStr.push_back(rowNamesRightJustified);
		}

		//Add column data from strData[row]
		for (int col = 0; col < strData[row].size(); col++) {
			colStrJustified = ljust(colMaxLen[col], strData[row][col]);
			rowStr.push_back(colStrJustified);
		}

		// Join rowStr by " | "
		finalRowStr = joinVect(rowStr, " | ");
		dataOut << "| " << finalRowStr << " |" << endl;
		dataOut << "+-" << border << "-+" << endl;
		rowStr.clear(); //clear vector string
	}
}
void PrintTableByVect(string title, vector<string> rowNames, vector<string> colNames, vector<vector<double>> data) {
  vector<vector<string>> strData = convertDVectToSVect(data);
  PrintTableByVect(title, rowNames, colNames, strData);
}

//function to display table
void PrintTableByVect(string title, vector<string> rowNames, vector<string> colNames, vector<vector<string>> strData) {

	vector<int> colMaxLen;
	bool noRowNames = rowNames.size() == 0;
	//Find the maximum length for row names
	int rowMaxLen = 0;
	if (!noRowNames)
		rowMaxLen = findMaxInVect(rowNames);
	//Find the maximum length for columns
	colMaxLen = getColMaxLength(colNames, strData);
	//Create header string with colNames
	vector<string> header = getHeader(colNames, noRowNames, colMaxLen, rowMaxLen);
	//Join vector string element by " | "
	string strHeader = joinVect(header, " | ");
	//Create Border
	string border = getBorder(header);
	//Print Table

	cout << title << endl << endl;
	printHeader(strHeader, border);
	printTableData(noRowNames, rowMaxLen, rowNames, colMaxLen, strData, border);
}

void printHeader(string strHeader, string border) {
	cout << "+-" << border << "-+" << endl;
	cout << "| " << strHeader << " |" << endl;
	cout << "+-" << border << "-+" << endl;
}

void printTableData(bool noRowNames, int rowMaxLen, vector<string>rowNames, vector<int> colMaxLen, vector<vector<string>> strData, string border) {

	//Show all rows of data
	string finalRowStr;
	string colStrLeftJustified;
	for (int row = 0; row < strData.size(); row++) {
		//Create row string
		//Add row name as the first element in rowStr
		vector<string> rowStr;
		if (noRowNames) {
			rowStr = {};
		}
		else {
			string rowNamesRightJustified = rjust(rowMaxLen, rowNames[row]);
			rowStr.push_back(rowNamesRightJustified);
		}
		//Add column data from strData[row]
		for (int col = 0; col < strData[row].size(); col++) {
			colStrLeftJustified = ljust(colMaxLen[col], strData[row][col]);
			rowStr.push_back(colStrLeftJustified);
		}
		// Join rowStr by " | "
		finalRowStr = joinVect(rowStr, " | ");
		cout << "| " << finalRowStr << " |" << endl;
		cout << "+-" << border << "-+" << endl;
		rowStr.clear(); //clear vector string
	}
}
//Export Txt and Display Data End****//