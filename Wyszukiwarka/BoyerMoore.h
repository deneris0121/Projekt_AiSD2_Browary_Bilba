#ifndef BOYERMOORE_H
#define BOYERMOORE_H
#include <iostream>
#include <vector>
using namespace std;
class BoyerMoore {
private:
    string text;
    string pattern;

    //tworzy tablice potrzebnej do Bad-character-heuristic
    vector<int> buildBadCharTable();

    //tworzy tablice potrzebnej do good-suffix-heuristic (na wykladzie BMNext)
    vector<int> buildGoodSuffixTable();

public:
    //konstruktor
    BoyerMoore(const string& txt, const string& pattern);

    //Algorytm BM do wyszukiwania wykorzystujacy obie heurestyki(bad i good)
    vector<int> search();
};
#endif