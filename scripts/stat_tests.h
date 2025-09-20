#ifndef STAT_TESTS_H
#define STAT_TESTS_H


#include<vector>
#include<string>
using namespace std;

pair<double, string> chiSquaredTest(const vector<int>& numbers, double confidenceLevel);
pair<double, string> kolmogorovSmirnovTest(const vector<double>& numbers, double confidenceLevel);

#endif