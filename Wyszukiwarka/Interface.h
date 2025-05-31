#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <vector>
using namespace std;
class Interface {
private:
    //kolorki
    const string RED = "\033[1;31m";
    const string RESET = "\033[0m";

public:
    //odczytuje plik i zapisuje zawartosc do string-a
    bool odczytaj(const string& filename, string& text);

    //wypisuje tekst
    void wypisz(const string& text, const vector<int>& positions, int patternLen);

    //wybiera wyszukiwarke i na niej dziala
    void wybor(const string& text, const string& pattern, int wybor);
};

#endif
