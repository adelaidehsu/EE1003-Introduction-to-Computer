//
//  find.cpp
//  
//
//  Created by b04705036 on 4/24/18.
//
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int main ()
{
    unsigned long long int phi = 0;
    unsigned long long int e = 0;
    string line;
    
    ifstream infile("cryptan.txt");
    while(getline(infile, line))
    {
        stringstream ss;
        ss << line;
        if(e == 0)
            ss >> e;
        else
            ss >> phi;
    }
    infile.close();
    
    unsigned long long int o_phi = phi;
    //Euclidean
    signed long long int d0, d1, r0, r1, d, r;
    d0 = 1; r0 = 0;
    d1 = 0; r1 = 1;
    d = 0; r = 1;
    signed long long int k = e % phi;
    signed long long int q = (e - k) / phi;
    while(k)
    {
        d = d0 - q*d1;
        r = r0 - q*r1;
        d0 = d1;
        r0 = r1;
        d1 = d;
        r1 = r;
        e = phi;
        phi = k;
        k = e % phi;
        q = (e - k) / phi;
    }
    
    if(d < 0)
    {
        d = d + o_phi;
    }
    
    ofstream ofile("cryptan_result.txt");
    ofile << d;
    ofile.close();
    
    return 0;
}
