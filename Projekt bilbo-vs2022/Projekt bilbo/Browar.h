#ifndef BROWAR_H
#define BROWAR_H
#include "Wezel.h"
class Browar : public Wezel
{
private:
    //ile jeczmienia moze przetworzyc browar
    int przetworzenie;
public:
    Browar(int x_, int y_, int przetworzenie_);

    //wyswietl informacje o browarze
    void wyswietl_info();
};
#endif
