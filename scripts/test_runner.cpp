#include<bits/stdc++.h>
#include "stat_tests.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <input_file> <mode: chi|ks> <confidence: 0.95|0.99> <results_file>\n";
        return 1;
    }

    string filename = argv[1];
    string mode = argv[2];
    double confidence = stod(argv[3]);
    string results_file = argv[4];

    ifstream in(filename);
    if(!in){
        cerr<<"Cannot open file."<<filename<<endl;
        return 1;
    }


    ofstream out_results(results_file, ios::app);
    if(!out_results){
        cerr << "Cannot open " << results_file << " for writing\n";
        return 1;
    }


    string line;
    getline(in, line); // I wrote this line to skip the first line, the info about seed.
    
    if(mode == "chi"){
        vector<int> numbers;
        int num;
        while(in >> num){
            numbers.push_back(num);
        }

        auto [stat, conclusion] = chiSquaredTest(numbers, confidence);
        out_results << "File: " << filename << "\n";
        out_results << "Chi-Square Statistic = " << stat << "\n";
        out_results << "Confidence Level = " << confidence << "\n";
        out_results << "Conclusion = " << conclusion << "\n\n";

        cout<<"Chi-Square test completed for "<<filename<<"\n";
    }else if(mode == "ks"){
        vector<double>numbers;
        double num;
        while(in >> num){
            numbers.push_back(num);
        }
        auto [stat, conclusion] = kolmogorovSmirnovTest(numbers, confidence);

        out_results << "File: " << filename << "\n";
        out_results << "KS Statistic = " << stat << "\n";
        out_results << "Confidence Level = " << confidence << "\n";
        out_results << "Conclusion = " << conclusion << "\n\n";

        cout<< "KS test completed for "<<filename<< "\n";
    }
    else{
        cerr<< "Invalid Mode. Use chi or ks.\n";
        return 1;
    }

    in.close();
    out_results.close();
    return 0;
}