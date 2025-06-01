#include <iostream>
#include <string>
#include "BoyerMoore.h"
#include "KnuthMorrisPratt.h"
#include "Interface.h"
#include "Dekoder.h"

using namespace std;

int main() {

    Interface interface;
    string text;
    string filename = "../Projekt bilbo-vsc/output/wynik.txt";
    if (!interface.odczytaj(filename,text)) {
        return 1;
    }
    cout<<"Wybierz wyszukiwarke"<<endl
        <<"1. Wyszukiwarka Knutha-Morrisa-Pratta"<<endl
        <<"2. Wyszukiwarka Boyera-Moore'a"<<endl;
    int wybor; 
    cin>>wybor;

    cin.ignore();

    string pattern;
    cout << "Podaj wzorzec do wyszukania: ";
    getline(cin, pattern);

    interface.wybor(text,pattern,wybor);

    Dekoder dekoder;
    dekoder.decompress("../Projekt bilbo-vsc/output/wynik.bin","../Projekt bilbo-vsc/output/zdekompresowany.txt");


    return 0;
}
