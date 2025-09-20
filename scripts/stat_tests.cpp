#include <bits/stdc++.h>

using namespace std;

// Chi-Squared Test

pair<double, string> chiSquaredTest(const vector<int>& numbers, double confidenceLevel){
    const int k = 100;

    vector<int> observedCounts(k,0);

    for(int num: numbers){
        int index = (num-1)/10;
        observedCounts[index]++;
    }

    double n = numbers.size();

    double expectedCount = n/k;
    if(expectedCount == 0){
        return {0.0, "Cannot perform test with zero expected count."};
    }

    double chiSquaredStatistic = 0.0;
    for(int i = 0; i<k; ++i){
        chiSquaredStatistic += pow(observedCounts[i]-expectedCount, 2)/expectedCount;
    }

    int degreeOfFreedom = k-1;

    unordered_map<int, pair<double, double>>criticalValues = {
        {99, {123.225, 134.420}}
    };

    double criticalValue;
    string conclusion;

    if(criticalValues.find(degreeOfFreedom) != criticalValues.end()){
        if(confidenceLevel == 0.95){
            criticalValue = criticalValues.at(degreeOfFreedom).first;
        }else if(confidenceLevel == 0.99){
            criticalValue = criticalValues.at(degreeOfFreedom).second;
        }else{
            return {chiSquaredStatistic, "Unsupported confidence level."};
        }
    }else{
        return {chiSquaredStatistic, "Unsupported degree of freedom."};
    }

    if(chiSquaredStatistic < criticalValue){
        conclusion = "Random";
    }else{
        conclusion = "Not Random";
    }

    return {chiSquaredStatistic, conclusion};
}



// Kolmogorov smirnov test


pair<double, string> kolmogorovSmirnovTest(const vector<double>& numbers, double confidenceLevel){
    vector<double> sortedNumbers = numbers;
    sort(sortedNumbers.begin(), sortedNumbers.end());

    double n = sortedNumbers.size();

    double dStatistic = 0.0;

    for(int i = 0; i< n; ++i){
        double y_i = sortedNumbers[i];

        double f_y_i = y_i/5.0;

        double dPlus = f_y_i - ((double)i/ n);
        double dMinus = ((double)(i + 1)/n)- f_y_i;

        dStatistic = max(dStatistic, max(dPlus, dMinus));
    }

    unordered_map<double, double> criticalValues = {
        {0.05,0.24},
        {0.01,0.29}
    };

    double criticalValue;
    string conclusion;

    if(confidenceLevel == 0.95){
        criticalValue = criticalValues.at(0.05);
    }else if(confidenceLevel == 0.99){
        criticalValue = criticalValues.at(0.01);
    }else{
        return {dStatistic, "Unsupported confidence level."};
    }


    if(dStatistic < criticalValue){
        conclusion = "Random";
    }else{
        conclusion = "Not Random";
    }

    return {dStatistic, conclusion};
}