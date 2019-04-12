
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <utility>
using namespace std;

/************************************
*  Note that in general using global
*  variables is a bad habit.
*  I use globals here because I don't 
*  want to scare you with "double***"
*************************************/

int m;
int n;
double **v;  // n*(m+1) 2D-array
double **h;  // (n+1)*m 2D-array

// For internal use only. Do not really use them directly
double *real_v;
double *real_h;

void readParameters()
{
    ifstream ifs("input1", ifstream::binary);

    ifs.read((char*)&m, sizeof(int));
    ifs.read((char*)&n, sizeof(int));
	
	
    real_v = new double[n*(m+1)];
    real_h = new double[(n+1)*m];

    ifs.read((char*)real_v, sizeof(double)*n*(m+1));
    ifs.read((char*)real_h, sizeof(double)*(n+1)*m);

    v = new double*[n];
    for (int i=0; i<n; ++i){
        v[i] = &(real_v[i*(m+1)]);
		
	}
    h = new double*[n+1];
    for (int i=0; i<n+1; ++i){
        h[i] = &(real_h[i*m]);
	}

    ifs.close();
	
	
}

void release()
{

    delete []v;
    delete []h;

    delete []real_v;
    delete []real_h;
}

bool full(vector<vector<int> > tree)
{
    for(int i=0; i<=n; ++i)
    {
        for(int j=0; j<=m; ++j)
        {
            if(tree[i][j] == 0)
                return false;
        }
    }
    return true;
}
pair<int, int> findDmin(vector<vector<float> > d, vector<vector<int> > &tree)
{
    float min = INT_MAX;
    pair<int, int> np;
    for(int i=0; i<=n; ++i)
    {
        for(int j=0; j<=m; ++j)
        {
            if(d[i][j] < min && tree[i][j]==0)
            {
                min = d[i][j];
                np = make_pair(i,j);
            }
        }
    }
    tree[np.first][np.second] = 1;
    return np;
}
string direction(pair<int, int> prev, pair<int, int> next)
{
    if(prev.first == next.first)
    {
        if((prev.second < m) && (next.second == prev.second +1))
            return "r";
        else if((prev.second > 0) && (next.second == prev.second - 1))
            return "l";
    }
    if(prev.second == next.second)
    {
        if((prev.first < n) && (next.first == prev.first +1))
            return "d";
        else if((prev.first > 0) && (next.first == prev.first - 1))
            return "u";
    }
}
void updateD(pair<int, int> np, vector<vector<int> > tree, vector<vector<float> > &d, vector<vector<vector<pair<int, int> > > > &route)
{
    int row = np.first;
    int col = np.second;
    
    if(row >0 && tree[row-1][col]==0)
    {
        if(d[row-1][col] > d[row][col] + v[row-1][col])
        {
            d[row-1][col] = d[row][col] + v[row-1][col];
            route[row-1][col] = route[row][col];
            route[row-1][col].push_back(make_pair(row,col));
        }
        
    }
    if(col >0 && tree[row][col-1]==0)
    {
        if(d[row][col-1] > d[row][col] + h[row][col-1])
        {
            d[row][col-1] = d[row][col] + h[row][col-1];
            route[row][col-1] = route[row][col];
            route[row][col-1].push_back(make_pair(row,col));
        }
        
    }
    if(row <n && tree[row+1][col]==0)
    {
        if(d[row+1][col] > d[row][col] + v[row][col])
        {
            d[row+1][col] = d[row][col] + v[row][col];
            route[row+1][col] = route[row][col];
            route[row+1][col].push_back(make_pair(row,col));
        }
        
    }
    if(col <m && tree[row][col+1]==0)
    {
        if(d[row][col+1] > d[row][col] + h[row][col])
        {
            d[row][col+1] = d[row][col] + h[row][col];
            route[row][col+1] = route[row][col];
            route[row][col+1].push_back(make_pair(row,col));
        }
    }
}

int main()
{
    readParameters();
    /***************************
     *
     *   your code/functions here
     *
     ***************************/
    ofstream ofile("result.txt");
    vector<string> path;
    vector<vector<vector<pair<int, int> > > > route;
    vector<vector<float> > d;
    vector<vector<int> > tree;

    //initialize route for each node
    for(int i=0; i<=n; ++i)
    {
        vector<vector<pair<int, int> > > tmp;
        for(int j=0; j<=m; ++j)
        {
            vector<pair<int, int> > list;
            tmp.push_back(list);
        }
        route.push_back(tmp);
    }

    //initialize tree
    for(int i=0; i<=n; ++i)
    {
        vector<int> tmp;
        for(int j=0; j<=m; ++j)
        {
            tmp.push_back(0);
        }
        tree.push_back(tmp);
    }
    
    //initialize d
    for(int i=0; i<=n; ++i)
    {
        vector<float> tmp;
        for(int j=0; j<=m; ++j)
        {
            tmp.push_back(INT_MAX);
        }
        d.push_back(tmp);
    }
    
    d[0][0] = 0;
    d[0][1] = h[0][0];
    route[0][1].push_back(make_pair(0,0));
    d[1][0] = v[0][0];
    route[1][0].push_back(make_pair(0,0));
    tree[0][0] = 1;
    
    //iteration
    while(!full(tree))
    {
        pair<int, int> np = findDmin(d,tree);
        updateD(np, tree, d, route);
    }
    
    route[n][m].push_back(make_pair(n,m));
    ofile<<d[n][m]<<endl;
    for(int i=0; i< route[n][m].size()-1; ++i)
    {
        pair<int, int> prev = route[n][m][i];
        pair<int, int> next = route[n][m][i+1];
        path.push_back(direction(prev,next));
    }
    for(int i=0; i<path.size(); ++i)
    {
        ofile<<path[i];
    }
    ofile.close();
    
    release();
    return 0;
}

