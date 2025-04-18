#ifndef CWIARTKA_H
#define CWIARTKA_H

#include "Wezel.h"
#include <vector>

using namespace std;

class Cwiartka{
private:
	vector <Wezel> punkty_Cwiartki;
	int wydajnosc;
public:
    Cwiartka();
    void ustawWydaj(int w);
    void dodajWierzcholek(int x, int y);
    vector<Wezel> zwrocWierzcholki();
    int zwrocWydajnosc() const;
    double onliczPoleCwiartki();
};



#endif
