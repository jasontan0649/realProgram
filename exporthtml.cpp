#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "commonf.h"
#include "table.h" //temporary

using namespace std;

//function to export HTML
void exportHTML(string, string, vector<string>, vector<string>, vector<vector<double>>, string mode = "once");
void exportHTML(string, string, vector<string>, vector<string>, vector<vector<string>>, string mode = "once");

void titleHTML(string, ofstream&);
void tableHTML(vector<string>, vector<string>, vector<vector<string>>, ofstream&);
void thTable(vector<string>, ofstream&);
void tdTable(vector<vector<string>>, vector<string>, ofstream&);

//Export HTML

void exportHTML(string fileName, string title, vector<string> col, vector<string> th, vector<vector<double>> data, string mode) {
  vector<vector<string>> strData = convertDVectToSVect(data);
  exportHTML(fileName, title, col, th, data, mode);
}

void exportHTML(string fileName, string title, vector<string> col, vector<string> th, vector<vector<string>> strData, string mode) {
	if (!col.empty()) //the col is not empty
		th.insert(th.begin(), 1, ""); //apend empty item to 1st of vector

	ofstream dataOut;

  if(mode == "once" || mode == "new")
	  dataOut.open(fileName);
  else
    dataOut.open(fileName, ios_base::app);

  if(mode == "once" || mode == "new"){
    dataOut << "<html>" << endl << endl << "<head>" << endl ;
    titleHTML(title, dataOut);
    dataOut << "<body>" << endl << "</head>" << endl ;
  }

  dataOut << endl;
  tableHTML(th, col, strData, dataOut);
  
  if(mode == "once" || mode == "last")
	  dataOut << "</body>" << endl << "</html>" << endl;

	dataOut.close(); 
}

void titleHTML(string title, ofstream& dataOut) {
	dataOut << "\t<title>" << title << "</title>" << endl << endl;
}

void tableHTML(vector<string> th, vector<string> col, vector<vector<string>> data, ofstream& dataOut) {
	dataOut << "\t<table class=\"table table-dark\">" << endl;
	dataOut << "\t\t<tr>" << endl;
	thTable(th, dataOut);
	dataOut << "\t\t</tr>" << endl;
	tdTable(data, col, dataOut);
	dataOut << "\t</table>" << endl;
}

void thTable(vector<string> th, ofstream& dataOut) {
	for (int i = 0; i < th.size(); i++) {
		dataOut << "\t\t\t<th>" << th[i] << "</th>" << endl;
	}
}

void tdTable(vector<vector<string>> data, vector<string> col, ofstream& dataOut) {
	for (int i = 0; i < data.size(); i++) {
		dataOut << "\t\t<tr>" << endl;
		//Added for column
		if (!col.empty()) {
			dataOut << "\t\t\t<th>" << col[i] << "</th>" << endl;
		}
		//Added for column ended
		for (int j = 0; j < data[i].size(); j++) {
			dataOut << "\t\t\t<th style=\"text-align:right;\">";
			dataOut << data[i][j] << "</th>" << endl;
		}
		dataOut << "\t\t</tr>" << endl;
	}
}

//Export HTML ended//
