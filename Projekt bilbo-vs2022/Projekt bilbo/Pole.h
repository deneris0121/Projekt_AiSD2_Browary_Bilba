#ifndef POLE_H
#define POLE_H
#include "Wezel.h"
#include<vector>
using namespace std;
class Pole : public Wezel
{
private:
    //ile jeczmienia produkuje
    int jeczmien;
public:
    Pole();
    Pole(int x_, int y_, int jeczmien_);
    //wyswietl informacje o polu
    void wyswietl_info();
    bool operator<(const Pole& p) const;
    static int iloczynWektorowy(const Pole& O, const Pole& A, const Pole& B);
    static vector<Pole> algorytmGrahama(vector<Pole>& wezly);
};
#endif
