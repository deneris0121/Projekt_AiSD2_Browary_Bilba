#include "Interface.h"
#include "BoyerMoore.h"
#include "KnuthMorrisPratt.h"
#include <fstream>
#include <string>

using namespace std;

bool Interface::odczytaj(const string& filename, string& text) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Nie mozna otworzyc pliku: " << filename << endl;
        return false;
    }
    //odczyt calosci pliku
    text = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return true;
}

void Interface::wypisz(const string& text, const vector<int>& positions, int patternLen) {
    int current = 0;
    //wypisujemy tekst przed znalezionym dopasowniem, a samo dopasowanie na kolor 
    for (int pos : positions) {
        cout << text.substr(current, pos - current);
        cout << RED << text.substr(pos, patternLen) << RESET;
        current = pos + patternLen;
    }
    //wypisujemy pozostaly tekst
    if (current < text.length())
    {
        cout << text.substr(current);
    }
    cout << endl;
}

void Interface::wybor(const string& text, const string& pattern, int wybor){
    if(wybor == 1)
    {
        KnuthMorrisPratt searcherKMP(text, pattern);
        vector<int> wynik = searcherKMP.search();

        if (wynik.empty()) {
            cout << "Nie znaleziono wzorca." << endl;
        } else {
            cout << "Znaleziono " << wynik.size() << " wystapienia:\n";
            wypisz(text, wynik, pattern.length());
        }
    }
    else if(wybor == 2)
    {
        BoyerMoore searcherBM(text, pattern);
        vector<int> wynik = searcherBM.search();

        if (wynik.empty()) {
            cout << "Nie znaleziono wzorca." << endl;
        } else {
            cout << "Znaleziono " << wynik.size() << " wystapien:\n";
            wypisz(text, wynik, pattern.length());
        }
    }
    else{
        cout<<"Blad - nie ma takiej wyszukiwarki"<<endl;
    }

}
