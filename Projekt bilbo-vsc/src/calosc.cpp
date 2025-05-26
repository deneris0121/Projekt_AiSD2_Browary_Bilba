#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include "Browar.h"
#include "Karczma.h"
#include "Krawedz.h"
#include "Cwiartka.h"
#include "Pole.h"
#include "Wezel.h"
#include "Graf.h"
#include "FordFulkerson.h"
#include "Drukuj.h"
#include "Calosc.h"
#include "Zapis.h"
using namespace std;

//klasa do zapisu wynikow w pliku
Zapis zapisz("../output/wynik.txt");

//to samo co funkcja wyzej tylko ze dla pliku
vector<Pole> polaICwiartkizPliku(std::istream& in, int iloscp) {
    vector<Cwiartka> cw;
    vector<Pole> pl;
    vector<int> iloscwv;
    int iloscw, wydajnosc;

    for (int i = 0; i < 4; i++) {
        in >> iloscw;
        iloscwv.push_back(iloscw);

        in >> wydajnosc;
        Cwiartka c;
        c.ustawWydaj(wydajnosc);
        cw.push_back(c);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < iloscwv[i]; j++) {
            int x_, y_;
            in >> x_ >> y_;
            cw[i].dodajWierzcholek(x_, y_);
        }
    }

    iloscwv.clear();

    for (int i = 0; i < iloscp; i++) {
        in >> iloscw;
        iloscwv.push_back(iloscw);
    }

    for (int i = 0; i < iloscp; i++) {
        Pole p;
        for (int j = 0; j < iloscwv[i]; j++) {
            int x_, y_;
            in >> x_ >> y_;
            p.dodajPunkt(x_, y_);
        }
        pl.push_back(p);
    }
    
    for (int i = 0; i < pl.size(); i++) {
        vector<int> przypisaneCwiartki = pl[i].znajdzCwiartki(cw);
        if(przypisaneCwiartki.size() != 1){
            cout<<"BLAD2 ";
            zapisz.dopisz("BLAD2");
            return {};
        }
        for(int i=0;i<przypisaneCwiartki.size();i++){
            cout<<"pole "<< i+1 <<" lezy w :"<< przypisaneCwiartki[i]+1<<" Cwiartce"<<endl;
            zapisz.dopisz("pole "+to_string(i+1)+" lezy w :"+to_string(przypisaneCwiartki[i]+1)+" Cwiartce");
        }
        double sumaJeczmienia = 0;

        for (int id : przypisaneCwiartki) {
            double wartosc = pl[i].obliczCalkowitaWartoscJeczmienia(cw[id]);
            sumaJeczmienia += wartosc;
        }
        if(sumaJeczmienia < 1){
            cout<<"BLAD3 ";
            zapisz.dopisz("BLAD3");
            return {};
        }
        cout<<"calkowita wartosc jeczmienia dla pola "<< i+1 << ": "<< sumaJeczmienia <<endl;
        zapisz.dopisz("calkowita wartosc jeczmienia dla pola "+to_string(i+1)+" "+to_string(sumaJeczmienia));
        pl[i].ustawcalkowita_wartosc_jeczmienia(sumaJeczmienia);
        pl[i].ustawSredniaXY();
    }

    return pl;
}

int uruchomProgram()
{
    
    int ile;
    int ile_pol, ile_browarow, ile_karczm, ile_skrzyzowan, ile_krawedzi;
    vector<vector<int>> koszty_napraw;
    vector<vector<int>> macierz_sasiedztwa_zboze;
    vector<vector<int>> macierz_sasiedztwa_piwo;
    vector<vector<int>> macierz_sasiedztwa;

    //---------------------------> Wczytywanie z pliku <---------------------------
    fstream plik;
    plik.open("dane.txt", ios::in);
    if (!plik.good())
    {
        cout << "Blad przy wczytywaniu pliku!" << endl;
        return 1;
    }
    //vector pol
        
    plik >> ile_pol >> ile_browarow >> ile_karczm >> ile_skrzyzowan >> ile_krawedzi;

    vector<Pole> pola = polaICwiartkizPliku(plik, ile_pol);
    //vector browarow
    vector<Browar> browary;
    //vector karczm
    vector<Karczma> karczmy;
    //vector krawedzi
    vector<Krawedz> krawedzie;

    //ile pol w macierzy sasiedztwa
    ile = ile_skrzyzowan + 2;
    //macierz sasiedztwa wypelniona zerami
    macierz_sasiedztwa_zboze.resize(ile, vector<int>(ile, 0));
    macierz_sasiedztwa_piwo.resize(ile, vector<int>(ile, 0));
    macierz_sasiedztwa.resize(ile, vector<int>(ile, 0));
    koszty_napraw.resize(ile, vector<int>(ile, 0));

    for (int i = 0; i < pola.size(); i++)
    {
            
        macierz_sasiedztwa_zboze[ile_skrzyzowan][i] = pola[i].zwroccalkowita_wartosc_jeczmienia();
        macierz_sasiedztwa[ile_skrzyzowan][i] += pola[i].zwroccalkowita_wartosc_jeczmienia();
    }

    for (int i = 0; i < ile_browarow; i++)
    {
        int x_, y_;
        int przetworzenie_;
        plik >> x_ >> y_ >> przetworzenie_;
        browary.emplace_back(x_, y_, przetworzenie_);
    }

    for (int i = 0; i < ile_karczm; i++)
    {
        int x_, y_;
        int zapotrzebowanie_;
        plik >> x_ >> y_ >> zapotrzebowanie_;
        karczmy.emplace_back(x_, y_, zapotrzebowanie_);
        macierz_sasiedztwa_piwo[ile_skrzyzowan - ile_karczm + i][ile - 1] = zapotrzebowanie_;
        macierz_sasiedztwa[ile_skrzyzowan - ile_karczm + i][ile - 1] += zapotrzebowanie_;
    }

    for (int i = 0; i < ile_krawedzi; i++)
    {
        int x_;
        int y_;
        int naprawa_;
        int przepustowosc_zboze_ = 0;
        int przepustowosc_piwo_ = 0;
        plik >> x_ >> y_ >> przepustowosc_zboze_ >> przepustowosc_piwo_ >> naprawa_;
        krawedzie.emplace_back(x_, y_, przepustowosc_zboze_, przepustowosc_piwo_, naprawa_);
        macierz_sasiedztwa_zboze[x_][y_] = przepustowosc_zboze_;
        macierz_sasiedztwa_piwo[x_][y_] = przepustowosc_piwo_;
        koszty_napraw[x_][y_] = naprawa_;  //przydzielamy koszt naprawy dla kazdej krawedzi
        koszty_napraw[y_][x_] = -naprawa_; //krawedzie odwrotne maja koszt naprawy odwrotny, aby w razie potrzeby cofnac koszt

        if (przepustowosc_piwo_ == 0)
        {
            macierz_sasiedztwa[x_][y_] += przepustowosc_zboze_;
        }
        else
        {
            macierz_sasiedztwa[x_][y_] += przepustowosc_piwo_;
        }

    }
    plik.close();
    

    //-----------------------------> Drukowanie macierzy <-----------------------------

    //macierz kosztow naprawy drog
    //drukujMacierz(koszty_napraw, "Macierz kosztow naprawy drog:");

    //macierz sasiedztwa zborza
    //drukujMacierz(macierz_sasiedztwa_zboze, "Macierz sasiedztwa (zboze):");
  
    //macierz sasiedztwa piwa
    //drukujMacierz(macierz_sasiedztwa_piwo, "Macierz sasiedztwa (piwo):");

    //macierz sasiedztwa wszystko razem
    //drukujMacierz(macierz_sasiedztwa, "Macierz sasiedztwa (wszystko razem):");

    pair<int, int> przeplywIkoszt = minCostMaxFlow(macierz_sasiedztwa, koszty_napraw, ile - 2, ile - 1);
    if(przeplywIkoszt.first == 0){
        cout<<"BLAD1 ";
        return 1;
    }
    cout << "Maksymalny przeplyw piwa do karczm:        \n" << przeplywIkoszt.first << " piwa." << endl;
    cout << "Minimalny koszt naprawy drog do przeplywu: \n" << przeplywIkoszt.second << " sztuk zlota." << endl;

    // cout<<"Maksymalny przeplyw piwa do karczm: "<<fordFulkerson(macierz_sasiedztwa,ile-2,ile-1)<<endl;
    
    zapisz.dopisz("Maksymalny przeplyw piwa do karczm: "+to_string(przeplywIkoszt.first)+ " piwa.");
    zapisz.dopisz("Minimalny koszt naprawy drog do przeplywu: "+to_string(przeplywIkoszt.second)+ " sztuk zlota.");
    
    return 0;
}
