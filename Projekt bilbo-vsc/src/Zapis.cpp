#include "Zapis.h"
using namespace std;

// Konstruktor otwiera plik do zapisu
Zapis::Zapis(const std::string& fname) : nazwa(fname) {
    plik.open(nazwa, std::ios::app);
    if (!plik.good())
    {
        cout << "Blad przy otwieraniu pliku!" << endl;
    }
}

// Destruktor zamyka plik
Zapis::~Zapis() {
    if (plik.is_open()) {
        plik.close();
    }
}

// Dodaje wpis na końcu
void Zapis::dopisz(const std::string& dane) {
    //int count = countEntries();

    plik.clear(); // konieczne, jeśli było wcześniej czytanie
    plik.seekp(0, ios::end); // ustaw na koniec do pisania

    plik << dane << "\n";
    //plik.flush(); // wymuś zapis
}