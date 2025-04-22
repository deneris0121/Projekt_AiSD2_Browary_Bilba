#ifndef POLE_H
#define POLE_H
#include "Wezel.h"
#include "Cwiartka.h"
#include<vector>
using namespace std;
class Pole: Wezel{
private:
    vector<Wezel> granice_Pola;
    //ile jeczmienia produkuje
    double calkowita_wartosc_jeczmienia;
public:
    Pole();
  
    void dodajPunkt(int x, int y);
    vector<Wezel>zwrocWierzcholkiPola();
    double zwroccalkowita_wartosc_jeczmienia();
    double obliczPolePola();
    double obliczCalkowitaWartoscJeczmienia(Cwiartka& ktora);
    void ustawcalkowita_wartosc_jeczmienia(double wynik);
    void ustawSredniaXY();
    Wezel zwrocPunkty();
    vector<int> znajdzCwiartki(vector<Cwiartka>& cwiartki);
};
#endif
