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
void exportPCLRHtml(string, string, vector<string>, vector<string>, vector<vector<string>> ,vector<double>,vector<double>,double,double,double);
void PCHtml(vector<double>,vector<double>,double,ofstream&);
void LRHtml(vector<double>,vector<double>,double,double,double,ofstream&);

void exportPCLRHtml(string fileName, string title, vector<string> col, vector<string> th, vector<vector<string>> strData, vector<double> arrY,vector<double> arrX, double r, double m, double b){
  if (!col.empty()) //the col is not empty
		th.insert(th.begin(), 1, ""); //append empty item to 1st of vector

	ofstream dataOut;
  dataOut.open(fileName);

  dataOut << "<html>" << endl << endl << "<head>" << endl ;
  titleHTML(title, dataOut);
  dataOut << "</head>" << endl << "<body>" << endl ;

  dataOut << endl;
  tableHTML(th, col, strData, dataOut);
  PCHtml(arrY,arrX,r,dataOut);
  LRHtml(arrY,arrX,r,m,b,dataOut);

	dataOut << "</body>" << endl << "</html>" << endl;

	dataOut.close(); 

}

void PCHtml(vector<double> arrY,vector<double> arrX,double r,ofstream& dataOut){
  int numOfData = arrY.size();
  double sumArrY = sum(arrY);
  double sumArrX = sum(arrX);

  dataOut << "<p>" << "1. Pearson’s Correlation" << "</p>" << endl << endl ;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;r = (" << numOfData << "*" <<sum(productXY(arrY,arrX)) << " - " << sumArrY << "*" << sumArrX << ") / sqrt((" << numOfData << "*" << sum(sqVect(arrY)) << " - " << sumArrY << "*" << sumArrY << ") * (" << numOfData << "*" << sum(sqVect(arrX))<<  " - " << sumArrX << "*" << sumArrX << "))" << "</p>" << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;= " << toStr(r,2) << "</p>" << endl << endl;
   
}
void LRHtml(vector<double> arrY,vector<double>  arrX, double r, double m, double b,ofstream& dataOut){
  
  dataOut << "<p>" << "2. Linear Regression" << "</p>" << endl << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;m = " << toStr(r,2) << " * " << "("<< sd(arrY) << " / " << sd(arrX)<<")" << "</p>" << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;= " << toStr(m,2) << "</p>" << endl << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;b = " << mean(arrY) << " - (" << toStr(m,2) << " * " << (mean(arrX)) << ")" << "</p>" <<endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;= " << toStr(b,2) << "</p>" << endl << endl;
  dataOut << "<p>" << "&nbsp;&nbsp;&nbsp;&nbsp;" << linearRegression(arrY, arrX,r,m,b) << "</p>" << endl << endl;
}