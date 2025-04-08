#include<iostream>
#include "Krawedz.h"

using namespace std;
Krawedz::Krawedz(int start_, int koniec_, int przepustowosc_zboze_, int przepustowosc_piwo_, int naprawa_) : start(start_), koniec(koniec_), przepustowosc_zboze(przepustowosc_zboze_), przepustowosc_piwo(przepustowosc_piwo_), naprawa(naprawa_) {}
void Krawedz::wyswietl_info()
{
    cout << "Krawedz (od: " << start << ", do: " << koniec << ")\nIle zboza mozna przetransportowac: " << przepustowosc_zboze << "\nIle piwa mozna przetransportowac: " << przepustowosc_piwo << "\nKoszt naprawy drogi: " << naprawa << endl << endl;
}