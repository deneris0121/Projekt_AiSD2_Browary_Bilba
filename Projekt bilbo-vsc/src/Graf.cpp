#include "graf.h"
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

bool Dijkstra(vector<vector<int> >& graf, vector<vector<int> >& koszty_naprawy, vector<int>& rodzic, vector<int>& koszty_dojscia, vector<int>& potencjaly, int s, int t)
{
	bool znaleziono = false; // Zmienna stwierdzajaca, czy znaleziono sciezke
	int rozmiar_grafu = graf.size();
	vector<bool> odwiedzone(rozmiar_grafu, false); // Inicjacja wektora odwiedzone

	koszty_dojscia.assign(rozmiar_grafu, INT_MAX); // Inicjacja kosztow dojscia w kazdej iteracji Dijkstry
	koszty_dojscia[s] = 0;                         // Wierzcholek startowy ma koszt dojscia rowny 0

	/*
	Kolejka przechowuje:
		* koszty dojscia do wierzcholkow,
		* nieodwiedzone wierzcholki grafu.
	Sortuje ona elementy w kolejnosci rosnacej
	*/
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> kolejka;

	kolejka.push({0, s}); // Wierzcholek s na poczatek kolejki z kosztem dojscia 0
	rodzic[s] = -1;       // Nie ma rodzica, bo startowy

	while (!kolejka.empty()) // Dopoki kolejka nie jest pusta przeszukujemy graf
	{
		int u = kolejka.top().second; // Wybieramy element z najmniejszym kosztem dojscia z kolejki
		kolejka.pop();

		// Czy wierzcholek u zostal juz odwiedzony
		if (odwiedzone[u]) { continue; }
		odwiedzone[u] = true;

		for (int i = 0; i < rozmiar_grafu; i++) // Szukamy sasiadow u
		{
			// Czy krawedz od u do i ma wolne miejsce na przeplyw
			if (graf[u][i] > 0)
			{
				// Aktualizowanie kosztu naprawy danej krawedzi z uzyciem potencjalow, aby uniknac kosztow ujemnych
				int koszt_efektywny = koszty_naprawy[u][i] + potencjaly[u] - potencjaly[i];
				
				// Czy znaleziono tansza sciezke od obecnej
				if (koszty_dojscia[i] > koszty_dojscia[u] + koszt_efektywny)
				{
					// Modyfikacja obecnego kosztu dojscia do danego wierzcholka
					koszty_dojscia[i] = koszty_dojscia[u] + koszt_efektywny;
					rodzic[i] = u; // Nowym rodzicem i staje sie u
					
					// Jesli dotarlismy do t, jakas sciezka zostala znaleziona. Nie dodajemy t do kolejki
					if (i == t) { znaleziono = true; }

					kolejka.push({koszty_dojscia[i], i}); // Dodajemy do kolejki wierzcholek i
				}
			}
		}
	}

	/* Zwracamy informacje, czy
	udalo sie znalezc koszt dojscia
	do wierzcholka koncowego,
	czyli tym samym - sciezke */
	return znaleziono;
}

void aktualizacjaPotencjalow(int rozmiar, vector<int>& koszty_dojscia, vector<int>& potencjaly) {
    for (int i = 0; i < rozmiar; i++) {
        if (koszty_dojscia[i] < INT_MAX) {
            potencjaly[i] += koszty_dojscia[i];
        }
    }
}

pair<int, int> SSP(vector<vector<int>>& graf, vector<vector<int>>& koszty_naprawy, int s, int t)
{
	int rozmiar = graf.size();
	vector<vector<int>> grafkopia = graf; // Kopia macierzy sasiedztwa
	
	vector<int> rodzic(rozmiar);         // Tablica do przechowywania zakodowanych sciezek
	vector<int> koszty_dojscia;          // Koszty dojscia reprezentuja "najnowsze" koszty sumarycznie, aby dojsc do danego wierzcholka
	
	/* Potencjaly "zapisuja" poprzednie koszty dojscia,
	*  tworzac zaktualizowane, najnowsze koszty dojscia
	*  do danej krawedzi, z kazda iteracja Dijktry.
	*  Dzieki temu, nowe tablice koszty_dojscia
	*  staja sie tak naprawde roznicami nowych kosztow z sumami starych kosztow.
	*  Dziala to na podstawie tego, ze nowe sciezki beda naturalnie drozsze niz stare.
	*  Dzieki potencjalom, nigdy nie wystapia koszty ujemne, a co za tym idzie,
	*  Dijkstra bedzie zawsze dzialac. */
	vector<int> potencjaly(rozmiar, 0);  // Tablica "potencjalow" wierzcholkow (przesuniecia, aby nie wystapily ujemne koszty)

	int maxprzeplyw = 0; // Maksymalny przeplyw
	int minkoszt = 0;    // Minimalny koszt naprawy drog

	while (Dijkstra(grafkopia, koszty_naprawy, rodzic, koszty_dojscia, potencjaly, s, t)) //jak jest sciezka powiekszajaca
	{
		// Aktualizacja potencjalow po Dijkstrze
		aktualizacjaPotencjalow(rozmiar, koszty_dojscia, potencjaly);

		int przepustowosc = INT_MAX;

		for (int i = t; i != s; i = rodzic[i]) // Znajdowanie minimalnej przepustowosci sciezki
		{
			int j = rodzic[i];
			przepustowosc = min(przepustowosc, grafkopia[j][i]);
		}

		for (int i = t; i != s; i = rodzic[i]) // Aktualizowanie przepustowosci na biezaco i dodawanie przeplywu w druga strone
		{
			int j = rodzic[i];
			grafkopia[j][i] -= przepustowosc;
			grafkopia[i][j] += przepustowosc;

			// Dla kazdego browara przewozonego sciezka, uwzgledniamy koszty naprawy poszczegolnych drog
			minkoszt += przepustowosc * koszty_naprawy[j][i];
		}

		maxprzeplyw += przepustowosc;
	}

	return {maxprzeplyw, minkoszt};
}