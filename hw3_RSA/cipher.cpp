//
//  cipher.cpp
//  
//
//  Created by b04705036 on 4/24/18.
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    unsigned long long int N = 0;
    unsigned long long int e = 0;
    unsigned long long int m[10000/2] = {0};
    int Msize = 0;
    string inStr;
    
    ifstream keyfile("public_key.txt");
    keyfile>>N>>e;
    keyfile.close();
    
    ifstream textfile("plain.txt");
    getline(textfile, inStr);
    textfile.close();
    
    int size = inStr.size();
    
    if(size%2 == 0)
    {
        for(int i=0; i<(size/2); ++i)
        {
            m[i] = (int)inStr[2*i]*pow(2,8) + (int)inStr[2*i+1];
            Msize++;
        }
    }
    else
    {
        for(int i=0; i<(size-1)/2; ++i)
        {
            m[i] = (int)inStr[2*i]*pow(2,8) + (int)inStr[2*i+1];
            Msize++;
        }
        m[(size-1)/2] = (int)inStr[size-1]*pow(2,8);
        Msize++;
    }
    
    for(int i=0; i<Msize; ++i)
    {
        unsigned long long int k = m[i] % N;
        for(int j=0; j<e-1; ++j)
        {
            m[i] = k*m[i];
            m[i] = m[i] % N;
        }
    }
    
    ofstream ofile("secret.txt");
    for(int i=0; i<Msize; ++i)
    {
        ofile<<m[i]<<endl;
    }
    ofile.close();

    
    return 0;
}
