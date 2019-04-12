//
//  decipher.cpp
//  
//
//  Created by b04705036 on 4/24/18.
//
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    unsigned long long int N = 0;
    unsigned long long int d = 0;
    unsigned long long int c[10000/2] = {0};
    
    ifstream keyfile("private_key.txt");
    keyfile>>N>>d;
    keyfile.close();
    
    ifstream enfile("secret.txt");
    stringstream ss;
    int Csize = 0;
    string line;
    while(getline(enfile, line))
    {
        ss<<line;
        ss>>c[Csize];
        Csize++;
        ss.clear();
        ss.str("");
    }
    enfile.close();
    
    
    //decrypt
    for(int i=0; i<Csize; ++i)
    {
        int twos = 0;
        int index = 0;
        unsigned long long int buff = d;
        unsigned long long int buff2 = d;
        
        while(buff >= 2)
        {
            buff = buff / 2;
            twos++;
        }
        unsigned long long int mod[twos+1] = {0};
        short int twos_expo_b[twos+1] = {0};
        
        while(buff2 >= 1)
        {
            twos_expo_b[index] = buff2 % 2;
            buff2 = buff2 / 2;
            index++;
        }
        
        for(int j=0; j<twos+1; ++j)
        {
            unsigned long long int k = 0;
            if(twos_expo_b[j])
            {
                k = c[i] % N;
                mod[j] = k;
                for(int q=0; q<j; ++q)
                {
                    k = (k*k) % N;
                }
                mod[j] = k;
            }
            else
                mod[j] = 1;
        }
        
        unsigned long long int mul = (mod[0]*mod[1]) % N;
        for(int cnt =2; cnt<twos+1; ++cnt)
        {
            mul = (mul*mod[cnt]) % N;
        }
        
        c[i] = mul;
    }
    
  
    char A[Csize] = {0};
    char B[Csize] = {0};
    for(int i=0; i<Csize; ++i)
    {
        A[i] = (char)(c[i] / 256);
        if(c[i]%256 != 0)
            B[i] = (char)(c[i] % 256);
    }
   
    
    ofstream ofile("message.txt");
    for(int i=0; i<Csize; ++i)
    {
        ofile<<A[i]<<B[i];
    }
    ofile.close();
    
    return 0;
}
