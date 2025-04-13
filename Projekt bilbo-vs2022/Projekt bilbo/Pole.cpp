#include<iostream>
//#include "pch.h"
#include "Pole.h"
#include "Wezel.h"
#include "Merge_sort.h"



using namespace std;
Pole::Pole() : Wezel(0, 0), jeczmien(0) {}
Pole::Pole(int x_, int y_, int jeczmien_) : Wezel(x_, y_), jeczmien(jeczmien_) {}
bool Pole::operator<(const Pole& p) const {
    return(y < p.y) || (y == p.y && x < p.x);
}
void Pole::wyswietl_info()
{
    cout << "Pole (x: " << x << ", y: " << y << ")\nIlosc produkowanego jeczmienia: " << jeczmien << endl << endl;
}
int Pole::iloczynWektorowy(const Pole& O, const Pole& A, const Pole& B) {
    return (A.getX() - O.getX()) * (B.getY() - O.getY()) -
        (A.getY() - O.getY()) * (B.getX() - O.getX());
}
vector <Pole> Pole::algorytmGrahama(vector<Pole>& wezly) {
    if (wezly.size() <= 3)return wezly;
    Pole start = *min_element(wezly.begin(), wezly.end());
    mergeSort(wezly, 0, wezly.size() - 1, start);
    vector<Pole> powloka;

    for (Pole& p : wezly) {
        // Sprawdzamy, czy pow�oka ma co najmniej 2 punkty i czy punkt "p" jest zgodny z kierunkiem
        while (powloka.size() >= 2 && iloczynWektorowy(powloka[powloka.size() - 2], powloka[powloka.size() - 1], p) <= 0) {
            powloka.pop_back();  // Usuwamy ostatni punkt, je�li nie pasuje
        }
        powloka.push_back(p);  // Dodajemy punkt do pow�oki
    }

    return powloka;
}