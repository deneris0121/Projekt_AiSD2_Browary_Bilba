#ifndef KNUTHMORRISPRATT_H
#define KNUTHMORRISPRATT_H
#include <iostream>
#include <vector>
using namespace std;
class KnuthMorrisPratt {
private:
    string text;
    string pattern;

    // Budowanie tablicy prefiksowej
    vector<int> buildPrefixTable();

public:
    //konstruktor
    KnuthMorrisPratt(const string& txt, const string& pattern);

    // Szukanie wzorca w tekście, zwraca wektor indeksóws
    vector<int> search();
};
#endif