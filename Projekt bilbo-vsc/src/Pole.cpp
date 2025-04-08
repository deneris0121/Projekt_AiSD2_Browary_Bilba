#include<iostream>
#include "Pole.h"
#include"Wezel.h"

using namespace std;
Pole::Pole(int x_, int y_, int jeczmien_) : Wezel(x_, y_), jeczmien(jeczmien_) {}
void Pole::wyswietl_info()
{
    cout << "Pole (x: " << x << ", y: " << y << ")\nIlosc produkowanego jeczmienia: " << jeczmien << endl << endl;
}