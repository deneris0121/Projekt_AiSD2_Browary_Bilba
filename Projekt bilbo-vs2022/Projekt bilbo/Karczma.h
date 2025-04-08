#ifndef KARCZMA_H
#define KARCZMA_H
#include "Wezel.h"

class Karczma : public Wezel
{
private:
    //zapotrzebowanie na piwo w karczmie
    int zapotrzebowanie;
public:
    Karczma(int x_, int y_, int zapotrzebowanie_);

    //wyswietl informacje o browarze
    void wyswietl_info();
};
#endif