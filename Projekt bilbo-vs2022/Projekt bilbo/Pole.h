#ifndef POLE_H
#define POLE_H
#include "Wezel.h"
#include "Cwiartka.h"
#include<vector>
using namespace std;
class Pole{
private:
    vector<Wezel> granice_Pola;
    //ile jeczmienia produkuje
    double calkowita_wartosc_jeczmienia;
public:
    Pole();
    //Pole(int x_, int y_, int jeczmien_);
  
    void dodajPunkt(int x, int y);
    vector<Wezel>zwrocWierzcholkiPola();
    double zwroccalkowita_wartosc_jeczmienia();
    double obliczPolePola();
    double obliczCalkowitaWartoscJeczmienia(Cwiartka& ktora);
    void ustawcalkowita_wartosc_jeczmienia(Cwiartka& ktora);
};
#endif
