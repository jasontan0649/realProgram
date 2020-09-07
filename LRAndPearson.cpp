
#include <iostream>
#include <vector> 
#include <cmath>

#include "statistic.h"
#include "commonf.h"
using namespace std;

vector<double> sqVect(vector<double>);
vector<double> productXY(vector<double>,vector<double>);
double pearsonCorr(vector<double>,vector<double>);
double slope(double,vector<double>,vector<double>);
double y_Intercept(double,vector<double>,vector<double>);
string linearRegression(vector<double>,vector<double>);


vector<double> sqVect(vector<double> arr)
{
	vector<double> vect;
	for (int i = 0; i < arr.size(); i++)
	{
		vect.push_back(pow(arr[i], 2));
	}
	return vect;
}

vector<double> productXY(vector<double> arr1,vector<double> arr2){
  vector<double> vect;
  for (int i = 0; i < arr1.size() ; i++)
	{
		vect.push_back(arr1[i] * arr2[i]);
	}
  return vect;
}

double pearsonCorr(vector<double> arrY,vector<double> arrX){
  int n = arrY.size();

  return (n * sum(productXY(arrY,arrX)) - sum(arrY) * sum(arrX)) / sqrt((n * sum(sqVect(arrY)) - sum(arrY) * sum(arrY)) * (n * sum(sqVect(arrX)) - sum(arrX) * sum(arrX)));
}

//need to ask user to determine which one y which one x
double slope(double r,vector<double> arrY,vector<double> arrX){
   return r * (sd(arrY) / sd(arrX));
}

double y_Intercept(double m,vector<double> arrY,vector<double> arrX){
  return mean(arrY) - m * (mean(arrX));
}

string linearRegression(vector<double> arrY,vector<double> arrX){

  double r = pearsonCorr(arrY,arrX);
  double m = slope(r,arrY,arrX);
  double b = y_Intercept(m,arrY,arrX);
  string temp;
  if (b>0){
    temp ="y = "+ toStr(m,2)+"x"+" + "+toStr(b,2);
    
  }else{
    b = fabs(b);
    temp ="y = "+toStr(m,2)+"x"+" - "+toStr(b,2);
    ;
  }

  return temp;
}