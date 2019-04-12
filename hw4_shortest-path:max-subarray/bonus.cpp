//
//  bonus.cpp
//  
//
//  Created by Aliyah on 5/20/18.
//
//

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int findMin(vector<int> arr, int t_size, vector<int> &L1, vector<int> &L2)
{
    int t_sum = 0;
    for(int i=0; i<t_size; ++i)
        t_sum += arr[i];
    
    //initialize table
    vector<vector<int>> table;
    for(int i=0; i<=t_size; ++i)
    {
        vector<int> tmp;
        for(int j=0; j<= t_sum; ++j)
        {
            tmp.push_back(0);
        }
        table.push_back(tmp);
    }
    
    //zero-sum
    for(int i=0; i<= t_size; ++i)
        table[i][0] = 1;
    //sum-of-zero
    for(int i=0; i<= t_sum; ++i)
        table[0][i] = 0;
    //table filling
    for(int i=1; i<=t_size; ++i)
    {
        for(int j=1; j<= t_sum; ++j)
        {
            table[i][j] = table[i-1][j];
            if(arr[i-1] <= j)
                table[i][j] |= table[i-1][j-arr[i-1]];
        }
    }
    
    int diff = INT_MAX;
    int j_value;
    int i_value;
    for(int j=t_sum/2 ; j>=0; --j)
    {
        if(table[t_size][j] == 1)
        {
            diff = t_sum-2*j;
            j_value = j;
            break;
        }
    }
    
    std::sort(arr.begin(), arr.end());
    int S1 = arr[t_size-1];
    L1.push_back(arr[t_size-1]);
    int S2 = 0;
    for(int i=t_size-2; i>=0; --i)
    {
        if(abs(S1+arr[i] - S2) < abs(S2+arr[i] - S1))
        {
            L1.push_back(arr[i]);
            S1 += arr[i];
        }
        else
        {
            L2.push_back(arr[i]);
            S2 += arr[i];
        }
    }

    return diff;
    
}

int main()
{
    ifstream infile("bonus_input.txt");
    ofstream output("bonus_result.txt");
    string inStr;
    vector<int> arr;
    vector<int> L1;
    vector<int> L2;
    bool first = true;
    int t_size;
    
    getline(infile ,inStr);
    istringstream delim(inStr);
    string token;
    while(getline(delim, token, ' '))
    {
        stringstream ss;
        int num_token;
        ss << token;
        ss >> num_token;
        if(first)
        {
            t_size = num_token;
            first = false;
        }
        else
            arr.push_back(num_token);
    }
    
    int diff = findMin(arr, t_size, L1, L2);
    
    output<<diff<<endl;
    for(int i=0; i<L1.size(); ++i)
    {
        output<<L1[i]<<' ';
    }
    output<<endl;
    for(int i=0; i<L2.size(); ++i)
    {
        output<<L2[i]<<' ';
    }
    
    infile.close();
    output.close();
    return 0;
}
