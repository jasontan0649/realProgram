#include <vector>
#include <iostream>
#include <string>
using namespace std;

#include "commonf.h"
#include "statistic.h"

void distinctNum(vector<double>, vector<double>&, vector<int>&);


void distinctNum(vector<double> vect, vector<double> &res, vector<int> &count){
  sort(vect);
  res.push_back(vect[0]);
  count.push_back(1);

  for(int i = 1; i < vect.size(); i++){
    if(res.back() == vect[i]) {
      count.back()++;
    }else{
      res.push_back(vect[i]);
      count.push_back(1);
    }
  }
  
}