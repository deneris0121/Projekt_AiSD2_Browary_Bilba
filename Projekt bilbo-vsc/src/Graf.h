#ifndef GRAF_H
#define GRAF_H
#include<vector>
using namespace std;
bool bfs(vector<vector<int>>& graf, int s, int t, vector<int>& rodzic);
int fordFulkerson(vector<vector<int>>& graf, int s, int t);
#endif

