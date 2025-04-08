#ifndef POLE_H
#define POLE_H
#include "Wezel.h"
class Pole : public Wezel
{
private:
    //ile jeczmienia produkuje
    int jeczmien;
public:
    Pole(int x_, int y_, int jeczmien_);
    //wyswietl informacje o polu
    void wyswietl_info();

};
#endif
