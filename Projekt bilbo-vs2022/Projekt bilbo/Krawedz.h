#ifndef KRAWEDZ_H
#define KRAWEDZ_H
class Krawedz
{
private:
    //skad/dokad prowadzi droga
    int start, koniec;
    //ile zboza mozna przetransportowac ta droga
    int przepustowosc_zboze;
    //ile piwa mozna przetransportowac ta droga
    int przepustowosc_piwo;
    //ile kosztuje mozliwa naprawa drogi
    int naprawa;
public:
    Krawedz(int start_, int koniec_, int przepustowosc_zboze_, int przepustowosc_piwo_, int naprawa_);

    //wyswietl informacje o drodze
    void wyswietl_info();
};
#endif