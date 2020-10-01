#include <iostream>
#include <vector> 
#include <cmath>

#include "statistic.h"
#include "commonf.h"
//export data and table
#include "table.h" //display and output text file
using namespace std;

vector<double> sqVect(vector<double>);
vector<double> productXY(vector<double>,vector<double>);
double pearsonCorr(vector<double>,vector<double>);
double slope(double,vector<double>,vector<double>);
double y_Intercept(double,vector<double>,vector<double>);
string linearRegression(vector<double>,vector<double>,double,double,double);

//Display Calculation On console
void printComputationOfPC(vector<double>,vector<double>, double);
void printComputationOfLR(vector<double>,vector<double>,double,double,double);

//Export into txt file
void exportPCLRTxt(string,string,vector<string>,vector<string>,vector<vector<string>>,vector<double>,vector<double>,double,double,double,string mode="new");


vector<double> sqVect(vector<double> arr)
{
	vector<double> squares;
	for (int i = 0; i < arr.size(); i++)
	{
		squares.push_back(pow(arr[i], 2));
	}
	return squares;
}

vector<double> productXY(vector<double> arr1,vector<double> arr2){
  vector<double> products;
  int size = arr1.size();
  for (int i = 0; i < size; i++)
	{
		products.push_back(arr1[i] * arr2[i]);
	}
  return products;
}

double pearsonCorr(vector<double> arrY,vector<double>  arrX){
  int numOfData = arrY.size();

  double numerator = numOfData * sum(productXY(arrY,arrX)) - sum(arrY) * sum(arrX);
  double denoY = numOfData * sum(sqVect(arrY)) - sum(arrY) * sum(arrY);
  double denoX = numOfData * sum(sqVect(arrX)) - sum(arrX) * sum(arrX);
  return (numerator) / sqrt(denoY * denoX);
}

//need to ask user to determine which one y which one x
double slope(double r,vector<double> arrY,vector<double> arrX){
   return r * (sd(arrY) / sd(arrX));
}

double y_Intercept(double m,vector<double> arrY,vector<double> arrX){
  return mean(arrY) - m * (mean(arrX));
}

string linearRegression(vector<double> arrY,vector<double> arrX,double r, double m, double b){
  
  char sign = '-';
  if (b>0)
    sign = '+';

  return "y = " + toStr(m,2) + "x "+ sign + " " + toStr(abs(b),2);
}

//Display Calculation On console
void printComputationOfPC(vector<double> arrY,vector<double>  arrX,double r){
  int numOfData = arrY.size();
  
  cout << "1. Pearson’s Correlation" << endl << endl;
  cout << "   r = (" << numOfData << "*" <<sum(productXY(arrY,arrX)) << " - " << sum(arrY) << "*" << sum(arrX) << ")/ sqrt((" << numOfData << "*" << sum(sqVect(arrY)) << " - " << sum(arrY) << "*" << sum(arrY) << ") * (" << numOfData << "*" << sum(sqVect(arrX))<<  " - " << sum(arrX) << "*" << sum(arrX) << "))" << endl;
  cout << "     = " << toStr(r,2) << endl << endl;
   
}
void printComputationOfLR(vector<double> arrY,vector<double>  arrX, double r, double m, double b){
  
  cout << "2. Linear Regression" << endl << endl;
  cout << "   m = " << toStr(r,2) << " * " << "("<< sd(arrY) << "/" << sd(arrX)<<")" << endl;
  cout << "     = " << toStr(m,2) << endl << endl;
  cout << "   b = " << mean(arrY) << " - (" << toStr(m,2) << "*" << (mean(arrX)) << ")" <<endl;
  cout << "     = " << toStr(b,2) << endl << endl;
  cout << "   " << linearRegression(arrY, arrX,r,m,b) << endl << endl;
}

//Export into txt file and html file
void exportPCLRTxt(string fileName, string title, vector<string> rowNames, vector<string> colNames, vector<vector<string>> strData,vector<double> arrY,vector<double> arrX, double r, double m, double b,string mode){
  ofstream dataOut;
	
  dataOut.open(fileName);

  streambuf *psbuf, *backup;
  backup = cout.rdbuf();
  psbuf = dataOut.rdbuf();
  cout.rdbuf(psbuf);

  PrintTableByVect(title, rowNames, colNames, strData);
  printComputationOfPC(arrY, arrX, r);
  printComputationOfLR(arrY, arrX, r, m, b);

  cout.rdbuf(backup);

	dataOut.close();
}

