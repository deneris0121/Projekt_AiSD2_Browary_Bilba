#include<iostream>
#include "Browar.h"
using namespace std;

Browar::Browar(int x_, int y_, int przetworzenie_) : Wezel(x_, y_), przetworzenie(przetworzenie_) {}
void Browar::wyswietl_info()
{
    cout << "Browar (x: " << x << ", y: " << y << ")\nIle jeczmienia moze przetworzyc: " << przetworzenie << endl << endl;
}