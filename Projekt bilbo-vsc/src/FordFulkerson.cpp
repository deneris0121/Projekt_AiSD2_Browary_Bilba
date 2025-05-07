#include "FordFulkerson.h"
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
bool bfs(vector<vector<int>>& graf, int s, int t, vector<int>& rodzic)
{
	int rozmiar_grafu = graf.size();
	vector<bool> odwiedzone(rozmiar_grafu, false); //inicjacja wektora odwiedzone

	//kolejka przechowuje wierzcholki grafu, ktore jeszcze nie zostaly odwiedzone
	queue<int> kolejka;
	odwiedzone[s] = true; //wierzcholek s - odwiedzony
	kolejka.push(s); //wierzcholek s na poczatek kolejki
	rodzic[s] = -1; //nie ma rodzica bo startowy

	while (!kolejka.empty()) //dopoki kolejka nie jest pusta przeszukujemy graf
	{
		int u = kolejka.front(); //wybieramy pierwszy element kolejki
		kolejka.pop();

		for (int i = 0; i < rozmiar_grafu; i++) //patrzymy na sasiadow u
		{
			if (odwiedzone[i] == false && graf[u][i] > 0) //czy wierzcholek i nie zostal jeszcze odwiedzony i czy istnieje krawedz od u do i
			{
				if (i == t) //jest sciezka do t 
				{
					rodzic[i] = u; //zapisanie sciezki
					return true; //jest sciezka = true
				}
				kolejka.push(i);
				rodzic[i] = u;
				odwiedzone[i] = true;
			}
		}
	}
	return false; //nie ma sciezki = false
}
int fordFulkerson(vector<vector<int>>& graf, int s, int t)
{
	int rozmiar = graf.size();
	vector<vector<int>> grafkopia = graf; //kopia macierzy sasiedztwa


	vector<int> rodzic(rozmiar); //tablica do przechowywania sciezki w drzewie bfs

	int maxprzeplyw = 0; //maksymalny przeplyw

	while (bfs(grafkopia, s, t, rodzic)) //jak jest sciezka powiekszajaca
	{
		int przepustowosc = 1000000;

		for (int i = t; i != s; i = rodzic[i]) //znajdowanie minimalnej przepustowosci sciezki
		{
			int j = rodzic[i];
			przepustowosc = min(przepustowosc, grafkopia[j][i]);
		}

		for (int i = t; i != s; i = rodzic[i]) //aktualizowanie przepustowosci na biezaco i dodawanie przeplywu w druga strone
		{
			int j = rodzic[i];
			grafkopia[j][i] -= przepustowosc;
			grafkopia[i][j] += przepustowosc;

		}

		maxprzeplyw += przepustowosc;
	}

	return maxprzeplyw;
}