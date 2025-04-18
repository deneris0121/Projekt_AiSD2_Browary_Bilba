#include<iostream>
#include "pch.h"
#include "Pole.h"
#include "Wezel.h"
#include "Merge_sort.h"
#include "Cwiartka.h"



using namespace std;
Pole::Pole() :calkowita_wartosc_jeczmienia(0) {}
//Pole::Pole(int x_, int y_, int jeczmien_) : Wezel(x_, y_), calkowita_wartosc_jeczmienia(0) {}


void Pole::dodajPunkt(int x, int y)
{
    granice_Pola.emplace_back(x, y);
}
double Pole::zwroccalkowita_wartosc_jeczmienia() {
    return calkowita_wartosc_jeczmienia;
}
vector<Wezel> Pole::zwrocWierzcholkiPola()
{
    return granice_Pola;
}
double Pole::obliczPolePola( )
{
    vector<Wezel> pagp = Wezel::algorytmGrahama(this->zwrocWierzcholkiPola());
    double wynik = Wezel::obliczPole(pagp);
    return wynik;
}

double Pole::obliczCalkowitaWartoscJeczmienia(Cwiartka& ktora)
{
    double Jcale = ktora.zwrocWydajnosc();
    double Pcale = ktora.onliczPoleCwiartki();
    double Ppole = this->obliczPolePola();
    double wynik = (Jcale / Pcale) * Ppole;
    return wynik;
}
void Pole::ustawcalkowita_wartosc_jeczmienia(Cwiartka& ktora) {
    double wynik = Pole::obliczCalkowitaWartoscJeczmienia(ktora);
    calkowita_wartosc_jeczmienia = wynik;
}



