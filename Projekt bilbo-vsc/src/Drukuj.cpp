#include <iostream>
#include <iomanip>
#include "drukuj.h"

using namespace std;

void drukujMacierz(const vector<vector<int>>& macierz, const string& opis) {
    cout << opis << endl;
    for (const auto& wiersz : macierz) {
        for (int wartosc : wiersz) {
            cout << setw(5) << wartosc;
        }
        cout << endl;
    }
    cout << endl;
}