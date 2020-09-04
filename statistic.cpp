#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double minVect(vector<double>);
double maxVect(vector<double>);
double median(vector<double>);
double mean(vector<double>);
double variance(vector<double>);
double sd(vector<double>);

double sum(vector<double>);
void sort(vector<double>&);

//Function
double sum(vector<double> arr) {
    double sum = 0;

    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    return sum;
}

void sort(vector<double>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                double tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

double minVect(vector<double> arr) {
    double res = arr[0];
    
    for (int i = 1; i < arr.size(); i++)
        if (res > arr[i])
            res = arr[i];
    return res;
}

double maxVect(vector<double> arr) {
    double res = arr[0];

    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > res)
            res = arr[i];
    return res;
}

double median(vector<double> arr) {
    sort(arr); //sort arr
    const int size = arr.size(); //get size

    if (size % 2)//if odd array length
        return arr[size / 2];
  
    return (arr[size / 2] + arr[size / 2 - 1]) / 2;
}

double mean(vector<double> arr) {
    return sum(arr) / arr.size();
}

double variance(vector<double> arr) {
    double meanRes = mean(arr); //get mean
    double sumNum = 0;
    const int size = arr.size();

    for (int i = 0; i < size; i++) {
        double tmp = arr[i] - meanRes;
        sumNum += tmp * tmp;
    }

    return sumNum / (size - 1);
}

double sd(vector<double> arr){
  return sqrt(variance(arr));
}

