#include "pch.h"
#include "Merge_sort.h"
#include <cmath>



using namespace std;

Pole start;

bool porownanieSkrajnychPunktow(const Pole& a, const Pole& b) {
	int c = start.iloczynWektorowy(start, a, b);
	if (c == 0) {
		double distA = hypot(a.getX() - start.getX(), a.getY() - start.getY());
		double distB = hypot(b.getX() - start.getX(), b.getY() - start.getY());
		return distA < distB;
	}
	return c > 0;
}
void merge(vector<Pole>& punkty, int lewy, int srodek, int prawy) {
	vector<Pole> L(punkty.begin() + lewy, punkty.begin() + srodek + 1);
	vector<Pole> R(punkty.begin() + srodek + 1, punkty.begin() + prawy + 1);

	int i = 0, j = 0, k = lewy;
	while (i < L.size() && j < R.size()) {
		if (porownanieSkrajnychPunktow(L[i], R[j])) {
			punkty[k++] = L[i++];
		}
		else {
			punkty[k++] = R[j++];
		}
	}
	while (i < L.size()) {
		punkty[k++] = L[i++];
	}
	while (j < R.size()) {
		punkty[k++] = R[j++];
	}
}
void mergeSort(vector<Pole>& punkty, int lewy, int prawy, Pole ref) {
	start = ref;
	if (lewy >= prawy) return;
	int srodek = (lewy + prawy) / 2;
	mergeSort(punkty, lewy, srodek, start);
	mergeSort(punkty, srodek + 1, prawy, start);
	merge(punkty, lewy, srodek, prawy);
}