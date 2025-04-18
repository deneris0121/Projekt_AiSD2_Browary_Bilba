#include <vector>          // WA¯NE: przed innymi include, bo vector mo¿e byæ w nag³ówku
#include "pch.h"
#include "Cwiartka.h"
#include "Wezel.h"         // <-- MUSISZ to mieæ, by klasa Wezel by³a znana

using namespace std;       // lub zamiast tego u¿ywaj std::vector

Cwiartka::Cwiartka():wydajnosc(0){}

void Cwiartka::ustawWydaj(int w)
{
    wydajnosc = w;
}

void Cwiartka::dodajWierzcholek(int x, int y)
{
    punkty_Cwiartki.emplace_back(x, y);
}

vector<Wezel> Cwiartka::zwrocWierzcholki()
{
    return punkty_Cwiartki;
}

int Cwiartka::zwrocWydajnosc() const
{
    return wydajnosc;
}

double Cwiartka::onliczPoleCwiartki()
{
    vector<Wezel> pag = Wezel::algorytmGrahama(punkty_Cwiartki);
    double wynik = Wezel::obliczPole(pag);
    return wynik;
}
