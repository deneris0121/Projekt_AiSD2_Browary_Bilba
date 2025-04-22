#ifndef CWIARTKA_H
#define CWIARTKA_H

#include "Wezel.h"
#include <vector>

using namespace std;

class Cwiartka{
private:
	vector <Wezel> punkty_Cwiartki;
	double wydajnosc;
public:
    Cwiartka();
    void ustawWydaj(double w);
    void dodajWierzcholek(int x, int y);
    vector<Wezel> zwrocWierzcholki();
    int zwrocWydajnosc() const;
    double onliczPoleCwiartki();
    bool czyPunktSieZnajduje(Wezel& p);
    bool punktNaKrawedzi(Wezel& a, Wezel& b, Wezel& p);
};



#endif
