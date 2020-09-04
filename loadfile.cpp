#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "commonf.h"

using namespace std;

string loadFile(vector<string>&, vector<vector<double>>&);
string getFileName();
bool getColTitleRow(ifstream&, int&, vector<string>&, int&);
bool getTitleRow(ifstream&, vector<string>&);
bool getData(ifstream&, vector<vector<double>>&);
bool isColRowMatch(vector<vector<double>>, int, int);


string loadFile(vector<string>& title, vector<vector<double>>& data) {
	while (1) {
		int row = 0, col = 0; string file; ifstream f;
		data.clear(); // vector clear prior run to clean old data
		title.clear(); // vector clear prior run to clean old data
		file = getFileName();
		f.open(file);

		if (!f) { //check file exist && can open
			cout << file << " not found\nPlease try again" << endl;
			continue;
		}

		if (!getColTitleRow(f, col, title, row))//get column,title,row from file,check format
			continue;

		if (!getData(f, data)) //get data from file, check format
			continue;

		if (!isColRowMatch(data, col, row))//check col,row match with data given
			continue;

		f.close();
		return file;
	}
}

string getFileName() {
	string file;
	cout << "Please enter a CSV file name: ";
	getline(cin, file);
	return file + ".csv";
}

bool getColTitleRow(ifstream& f, int& col, vector<string>& title, int& row) {
	if (!(f >> col)) { //check column value, false if 0 or not int
		cout << "Unsupported format/Empty data\nPlease try again" << endl;
		return false;
	}

	if (!getTitleRow(f, title) || title.size() != col) { //get title from 
		cout << "Columns do not match\nPlease try again" << endl;
		return false;
	}

	if (!(f >> row)) { //check row value, false if 0 or not int
		cout << "Empty data\nPlease try again" << endl;
		return false;
	}

	return true;
}

bool getTitleRow(ifstream& f, vector<string>& title) {
	string line;
	f >> line;

	if (line.empty()) //empty data
		return false;

	//retrieve value by string streaming
	string val;
	istringstream titleStream(line);
	while (getline(titleStream, val, ',')) {
		if (val.empty()) {
			return false;
		}
		title.push_back(val);
	}

	return true;
}

bool getData(ifstream& f, vector<vector<double>>& data) {
	string line, val;

	while (f >> line) {
		istringstream  lineStream(line);
		data.emplace_back(); //append new vector if line not end
		while (getline(lineStream, val, ',')) {
			if (val.empty() || !isNum(val)) {
				cout << "Data contain non numeric value.\nPlease try again" << endl;
				return false;
			}
			data.back().push_back(stod(val)); //append data 
		}
	}

	return true; //append successful
}

bool isColRowMatch(vector<vector<double>> data, int col, int row) {
	if (row != data.size()) {
		cout << "Data row does not match with given input\nPlease try again" << endl;
		return false;
	}

	for (vector item : data)
		if (col != item.size()) {
			cout << "Data column does not match with given input\nPlease try again" << endl;
			return false;
		}

	return true;
}
//load file ended//