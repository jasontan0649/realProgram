#include <iostream>
#include <vector> 
#include <cmath>

#include "statistic.h"
#include "commonf.h"
#include "LRAndPearson.h"
//export data and table
#include "exporthtml.h"
#include "table.h" //display and output text file
using namespace std;

//Export into HTML File
void exportPCLRHtml(string, string, vector<string>, vector<string>, vector<vector<string>> ,vector<double>,vector<double>,double,double,double,string mode = "once");
void PCHtml(vector<double>,vector<double>,double,ofstream&);
void LRHtml(vector<double>,vector<double>,double,double,double,ofstream&);

void exportPCLRHtml(string fileName, string title, vector<string> col, vector<string> th, vector<vector<string>> strData, vector<double> arrY,vector<double> arrX, double r, double m, double b,string mode){
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
    dataOut << "</head>" << endl << "<body>" << endl ;
  }

  dataOut << endl;
  tableHTML(th, col, strData, dataOut);
  PCHtml(arrY,arrX,r,dataOut);
  LRHtml(arrY,arrX,r,m,b,dataOut);

  if(mode == "once" || mode == "last")
	  dataOut << "</body>" << endl << "</html>" << endl;

	dataOut.close(); 

}

void PCHtml(vector<double> arrY,vector<double>  arrX,double r,ofstream& dataOut){
  int numOfData = arrY.size();
  dataOut << "<p>" << "1. Pearson’s Correlation" << "</p>" << endl << endl ;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;r = (" << numOfData << "*" <<sum(productXY(arrY,arrX)) << " - " << sum(arrY) << "*" << sum(arrX) << ")/ sqrt((" << numOfData << "*" << sum(sqVect(arrY)) << " - " << sum(arrY) << "*" << sum(arrY) << ") * (" << numOfData << "*" << sum(sqVect(arrX))<<  " - " << sum(arrX) << "*" << sum(arrX) << "))" << "</p>" << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;= " << toStr(r,2) << "</p>" << endl << endl;
   
}
void LRHtml(vector<double> arrY,vector<double>  arrX, double r, double m, double b,ofstream& dataOut){
  
  dataOut << "<p>" << "2. Linear Regression" << "</p>" << endl << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;m = " << toStr(r,2) << " * " << "("<< sd(arrY) << "/" << sd(arrX)<<")" << "</p>" << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;= " << toStr(m,2) << "</p>" << endl << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;b = " << mean(arrY) << " - (" << toStr(m,2) << "*" << (mean(arrX)) << ")" << "</p>" <<endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;= " << toStr(b,2) << "</p>" << endl << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;" << linearRegression(arrY, arrX,r,m,b) << "</p>" << endl << endl;
}