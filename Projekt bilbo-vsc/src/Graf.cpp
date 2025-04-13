#include "graf.h"
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

bool Dijkstra(vector<vector<int>>& graf, vector<vector<int>>& koszty_naprawy, vector<int>& rodzic, vector<int>& koszty_dojscia, vector<int>& potencjaly, int s, int t)
{
	int rozmiar_grafu = graf.size();
	vector<bool> odwiedzone(rozmiar_grafu, false); //inicjacja wektora odwiedzone

	koszty_dojscia.assign(rozmiar_grafu, INT_MAX); //inicjacja kosztow dojscia w kazdej iteracji Dijkstry
	koszty_dojscia[s] = 0;                         //wierzcholek startowy ma koszt dojscia do niego rowny 0

	//kolejka przechowuje wierzcholki grafu, ktore jeszcze nie zostaly odwiedzone, wraz z ich kosztem dojscia
	//sortuje ona elementy w kolejnosci rosnacej
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> kolejka;

	kolejka.push({0, s}); //wierzcholek s na poczatek kolejki z kosztem dojscia 0
	rodzic[s] = -1;       //nie ma rodzica bo startowy

	while (!kolejka.empty()) //dopoki kolejka nie jest pusta przeszukujemy graf
	{
		int u = kolejka.top().second; //wybieramy element z najmniejszym kosztem dojscia z kolejki
		kolejka.pop();

		//czy wierzcholek u zostal juz odwiedzony
		if (odwiedzone[u]) { continue; }
		odwiedzone[u] = true;

		for (int i = 0; i < rozmiar_grafu; i++) //patrzymy na sasiadow u
		{
			//czy krawedz od u do i ma wolne miejsce na przeplyw
			if (graf[u][i] > 0)
			{
				//aktualizowanie kosztu krawedzi z uzyciem potencjalow, aby uniknac kosztow ujemnych
				int koszt_efektywny = koszty_naprawy[u][i] + potencjaly[u] - potencjaly[i];
				
				//czy znaleziono tansza sciezke od obecnej
				if (koszty_dojscia[i] > koszty_dojscia[u] + koszt_efektywny) {
					
					//modyfikacja obecnego kosztu dojscia do danego wierzcholka
					koszty_dojscia[i] = koszty_dojscia[u] + koszt_efektywny;
					rodzic[i] = u;
					kolejka.push({koszty_dojscia[i], i});
				}
			}
		}
	}

	//zwracamy informacje, czy udalo sie znalezc koszt dojscia do wierzcholka koncowego
	return koszty_dojscia[t] != INT_MAX;
}

pair<int, int> minCostMaxFlow(vector<vector<int>>& graf, vector<vector<int>>& koszty_naprawy, int s, int t)
{
	int rozmiar = graf.size();
	vector<vector<int>> grafkopia = graf; //kopia macierzy sasiedztwa
	
	vector<int> rodzic(rozmiar);         //tablica do przechowywania zakodowanych sciezek
	vector<int> koszty_dojscia(rozmiar); //tablica kosztow dojscia dla kazdego wierzcholka
	vector<int> potencjaly(rozmiar, 0);  //tablica "potencjalow" wierzcholkow (przesuniecia, aby nie wystapily ujemne koszty)

	int maxprzeplyw = 0; //maksymalny przeplyw
	int minkoszt = 0;    //minimalny koszt naprawy drog

	while (Dijkstra(grafkopia, koszty_naprawy, rodzic, koszty_dojscia, potencjaly, s, t)) //jak jest sciezka powiekszajaca
	{
		//aktualizacja potencjalow po Dijkstrze
        for (int i = 0; i < rozmiar; i++) {
            if (koszty_dojscia[i] < INT_MAX) {
                potencjaly[i] += koszty_dojscia[i];
            }
        }

		int przepustowosc = INT_MAX;

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

			//dla kazdego browara przewozonego sciezka, uwzgledniamy koszty naprawy poszczegolnych drog
			minkoszt += przepustowosc * koszty_naprawy[j][i];
		}

		maxprzeplyw += przepustowosc;
	}

	return {maxprzeplyw, minkoszt};
}