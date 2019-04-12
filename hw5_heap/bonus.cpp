//
//  bonus.cpp
//  
//
//  Created by Aliyah on 6/3/18.
//
//

#include <fstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
#include "heap.h"

int main()
{
    vector<float> A;
    vector<float> B;
    vector<float> sum;
    Heap<float, pair<int, int>> tree;
    
    int n;
    ifstream infile("bonus.txt");
    infile >> n;
    
    float *keyA = new float[n];
    float *keyB = new float[n];
    for(int i=0; i<n; ++i)
    {
        infile >> keyA[i];
        A.push_back(keyA[i]);
    }
    
    for(int i=0; i<n; ++i)
    {
        infile >> keyB[i];
        B.push_back(keyB[i]);
    }
    
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    
    vector<bool> tmp;
    for(int i=0; i<n; ++i)
    {
        tmp.push_back(false);
    }
    vector<vector<bool> > visited;
    for(int i=0; i<n; ++i)
    {
        visited.push_back(tmp);
    }
    
    tree.push(A[0]+B[0], make_pair(0,0));
    visited[0][0] = true;
    int dx[2] = {0,1};
    int dy[2] = {1,0};
    
    for(int i=0; i<n; ++i)
    {
        cout<< tree.getTopKey()<<" ";
        pair<int, int> smallest = tree.pop();
        int small_A = smallest.first;
        int small_B = smallest.second;
        for(int j=0; j<2; j++)
        {
            int next_A = small_A+dx[j];
            int next_B = small_B+dy[j];
            if(next_A<n && next_B<n && next_A>=0 && next_B>=0)
            {
                if(!visited[next_A][next_B])
                {
                    tree.push(A[next_A]+B[next_B], make_pair(next_A,next_B));
                    visited[next_A][next_B] = true;
                }
            }
        }
        
    }
    
    infile.close();
    delete []keyA;
    delete []keyB;
    
    return 0;
}
