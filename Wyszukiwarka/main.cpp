#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "BoyerMoore.h"

using namespace std;

int main() {
    
    BoyerMoore searcher;

    string filename = "../Projekt bilbo-vsc/output/wynik.txt";
    if (!searcher.odczytaj(filename)) {
        return 1;
    }

    string pattern;
    cout << "Podaj wzorzec do wyszukania: ";
    getline(cin, pattern);

    vector<int> wynik = searcher.search(pattern);

    if (wynik.empty()) {
        cout << "Nie znaleziono wzorca." << endl;
    } else {
        cout << "Znaleziono " << wynik.size() << " wystapien:\n";
        searcher.wypisz(wynik, pattern.length());
    }


    return 0;
}
