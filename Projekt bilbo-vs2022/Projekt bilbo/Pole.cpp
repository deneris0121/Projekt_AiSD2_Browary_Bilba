#include<iostream>
#include "pch.h"
#include "Pole.h"
#include "Wezel.h"
#include "Merge_sort.h"
#include "Cwiartka.h"



using namespace std;
Pole::Pole() :Wezel(0,0), calkowita_wartosc_jeczmienia(0) {}


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
void Pole::ustawcalkowita_wartosc_jeczmienia(double wynik) {
    calkowita_wartosc_jeczmienia = wynik;
}

void Pole::ustawSredniaXY()
{
    double sumaX=0;
    double sumaY=0;
    if (granice_Pola.empty()) {
        this->x = 0;
        this->y = 0;
    }
    for (const Wezel& p : granice_Pola){
        sumaX += p.getX();
        sumaY += p.getY();
    }
    this-> x = sumaX / granice_Pola.size();
    this-> y = sumaY / granice_Pola.size();

}
//nie pamietam juz po co to zrobiłam chyba po to by potem ali było łatwo znajdować te punkty???
Wezel Pole::zwrocPunkty()
{
    return Wezel(x,y);
}
//dla kazdej cwiartki sprawdzane jest czy punkt się znajduje wewnatrz lub na granicy
vector<int> Pole::znajdzCwiartki(vector<Cwiartka>& cwiartki)
{
    vector<int> przypisaneCwiartki;

    for (int i = 0; i < cwiartki.size(); i++) {
        Cwiartka& c = cwiartki[i];

        for (Wezel& p : granice_Pola) {
            if (c.czyPunktSieZnajduje(p)) {
                przypisaneCwiartki.push_back(i);
                
                break;
            }
        }
    }

    return przypisaneCwiartki;
}



