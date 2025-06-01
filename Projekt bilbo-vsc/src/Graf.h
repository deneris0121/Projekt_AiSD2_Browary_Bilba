#ifndef GRAF_H
#define GRAF_H
#include<vector>

using namespace std;

bool Dijkstra(vector<vector<int>>& graf, vector<vector<int>>& koszty_naprawy, vector<int>& rodzic, vector<int>& koszty_dojscia, vector<int>& potencjaly, int s, int t);

void aktualizacjaPotencjalow(int rozmiar, vector<int>& koszty_dojscia, vector<int>& potencjaly);

pair<int, int> SSP(vector<vector<int>>& graf, vector<vector<int>>& koszty, int znaleziony_przeplyw, int s, int t);

#endif