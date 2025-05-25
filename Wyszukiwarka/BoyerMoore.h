#ifndef BoyerMoore_H
#define BoyerMoore_H
#include <iostream>
#include <vector>
using namespace std;
class BoyerMoore {
private:
    string text;
    //kolorki
    const string RED = "\033[1;31m";
    const string RESET = "\033[0m";

    //tworzy tablice potrzebnej do Bad-character-heuristic
    vector<int> buildBadCharTable(const string& pattern);

    //tworzy tablice potrzebnej do good-suffix-heuristic (na wykladzie BMNext)
    vector<int> buildGoodSuffixTable(const string& pattern);

public:
    //odczytuje tekst z podanego pliku
    bool odczytaj(const string& filename);

    //Algorytm BM do wyszukiwania wykorzystujacy obie heurestyki(bad i good)
    vector<int> search(const string& pattern);

    //wypisuje tekst
    void wypisz(const vector<int>& positions, int patternLen);
};
#endif