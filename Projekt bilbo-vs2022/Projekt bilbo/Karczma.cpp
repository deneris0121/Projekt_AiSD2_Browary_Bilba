#include<iostream>
#include "Karczma.h"

using namespace std;

Karczma::Karczma(int x_, int y_, int zapotrzebowanie_) : Wezel(x_, y_), zapotrzebowanie(zapotrzebowanie_) {}
void Karczma::wyswietl_info()
{
    cout << "Karczma (x: " << x << ", y: " << y << ")\nZapotrzebowanie na piwo: " << zapotrzebowanie << endl << endl;
}