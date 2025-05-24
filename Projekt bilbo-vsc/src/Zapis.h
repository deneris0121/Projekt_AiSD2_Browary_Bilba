#ifndef ZAPIS_H
#define ZAPIS_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Zapis {
private:
    string nazwa;
    fstream plik;

public:
    // Konstruktor otwiera plik do odczytu i zapisu
    Zapis(const string& fname);

    // Destruktor zamyka plik
    ~Zapis();

    //zmiana wartosci w pliku
    //void change();

    // Liczy wpisy
    //int countEntries();

    // Dodaje wpis na końcu
    void dopisz(const string& dane);

    // Zmienia wpis o danym indeksie
    //bool updateEntry(int index, const string& newText);
};
#endif