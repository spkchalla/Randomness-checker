#include<bits/stdc++.h>
#include<iomanip>

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 4){
        cerr<<"Usage: "<<argv[0]<<"<seed> <output_file> <mode: chi|ks>\n";
        return 1;
    }

    int seed = stoi(argv[1]);
    string filename = argv[2];
    string mode = argv[3];


    ofstream  out(filename);
    if(!out){
        cerr<<"Cannot open file"<<filename<<endl;
        return 1;
    }


    srand(seed);
    out<<"#seed = "<<seed<<"\n";

    if(mode == "chi"){
        for(int i = 0; i< 5000; i++){
            int num = (rand()% 1000)+1;
            out<<num<<"\n";
        }
    }else if(mode == "ks"){
        for(int i = 0; i< 30; i++){
            double num = (rand() / (double)RAND_MAX)*5.0;
            out<<fixed<<setprecision(6)<<num<<"\n";
        }
    }else{
        cerr<<"Invalid mode. Use chi or ks.\n";
        return 1;
    }

    out.close();
    return 0;
}