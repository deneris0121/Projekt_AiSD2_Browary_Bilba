#ifndef GRAF_H
#define GRAF_H
#include<vector>

using namespace std;

bool Dijkstra(vector<vector<int>>& graf, vector<vector<int>>& koszty_naprawy, vector<int>& rodzic, vector<int>& koszty_dojscia, vector<int>& potencjaly, int s, int t);
pair<int, int> minCostMaxFlow(vector<vector<int>>& graf, vector<vector<int>>& koszty, int s, int t);

#endif