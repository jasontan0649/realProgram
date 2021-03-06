#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "commonf.h"
#include "table.h" //temporary

using namespace std;

//function to export HTML
void exportHTML(string, string, vector<string>, vector<string>, vector<vector<double>>, string extra = "", string mode = "once");
void exportHTML(string, string, vector<string>, vector<string>, vector<vector<string>>, string extra = "", string mode = "once");

void titleHTML(string, ofstream&);
void tableHTML(vector<string>, vector<string>, vector<vector<string>>, ofstream&);
void thTable(vector<string>, ofstream&);
void tdTable(vector<vector<string>>, vector<string>, ofstream&);
void cssHTML(ofstream&);

//Export HTML

void exportHTML(string fileName, string title, vector<string> col, vector<string> th, vector<vector<double>> data,string extra, string mode) {
  vector<vector<string>> strData = convertDVectToSVect(data);
  exportHTML(fileName, title, col, th, strData, extra, mode);
}

void exportHTML(string fileName, string title, vector<string> col, vector<string> th, vector<vector<string>> strData, string extra, string mode) {
	if (!col.empty()) 	//the col is not empty
		th.insert(th.begin(), 1, ""); 	//append empty item to 1st of vector

	ofstream dataOut;

  if(mode == "once" || mode == "new")		// switch mode option for output 2 tables in 1 text file
	  dataOut.open(fileName);
  else
    dataOut.open(fileName, ios_base::app);

  if(mode == "once" || mode == "new"){
    dataOut << "<html>" << endl << endl << "<head>" << endl;
    titleHTML(title, dataOut);
		cssHTML(dataOut);
    dataOut << "</head>" << endl << "<body>" << endl;
  }
  
	dataOut << "\t<h2>" << title << "</h2>" << endl << endl;
	
	if(!extra.empty())					// displays a extra text (useful for mean)
    dataOut << "\t<p>" << extra << "</p>" << endl; 

  tableHTML(th, col, strData, dataOut);
  
  if(mode == "once" || mode == "last")
	  dataOut << "</body>" << endl << "</html>" << endl;

	dataOut.close(); 
}

// HTML format
void cssHTML(ofstream& dataOut){
	dataOut << "\t<style>" << endl;
	dataOut << "\t\ttable, th, td {" << endl;
  dataOut << "\t\t\tborder: 1px solid black;" << endl;
	dataOut << "\t\t\t}" << endl;
	dataOut << "\t</style>" << endl;
}

void titleHTML(string title, ofstream& dataOut) {
	dataOut << "\t<title>" << title << "</title>" << endl << endl;
}

void tableHTML(vector<string> th, vector<string> col, vector<vector<string>> data, ofstream& dataOut) {
	dataOut << "\t<table>" << endl;
	dataOut << "\t\t<tr>" << endl;
	thTable(th, dataOut);
	dataOut << "\t\t</tr>" << endl;
	tdTable(data, col, dataOut);
	dataOut << "\t</table>" << endl;
}

void thTable(vector<string> th, ofstream& dataOut) {			// display ID & title(s)
	for (int i = 0; i < th.size(); i++) {
		dataOut << "\t\t\t<th>" << th[i] << "</th>" << endl;
	}
}

void tdTable(vector<vector<string>> data, vector<string> col, ofstream& dataOut) {		// display data of table
	for (int i = 0; i < data.size(); i++) {
		dataOut << "\t\t<tr>" << endl;
		//Added for col
		if (!col.empty()) {
			dataOut << "\t\t\t<td>" << col[i] << "</td>" << endl;
		}
		//Added for col ended
		for (int j = 0; j < data[i].size(); j++) {
			dataOut << "\t\t\t<td style=\"text-align:right;\">";
			dataOut << data[i][j] << "</td>" << endl;
		}
		dataOut << "\t\t</tr>" << endl;
	}
}

//Export HTML ended//
