#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Browar.h"
#include "Karczma.h"
#include "Krawedz.h"
#include "Pole.h"
#include "Wezel.h"
#include "Graf.h"
#include "Drukuj.h"
#include "Calosc.h"
using namespace std;


int uruchomProgram()
{
    cout << "----------------------> Witaj w Shire! <----------------------" << endl << endl;
    int ile;
    int ile_pol, ile_browarow, ile_karczm, ile_skrzyzowan, ile_krawedzi;
    vector<vector<int>> koszty_napraw;
    vector<vector<int>> macierz_sasiedztwa_zboze;
    vector<vector<int>> macierz_sasiedztwa_piwo;
    vector<vector<int>> macierz_sasiedztwa;

    cout << "Wybierz jak chcesz wczytac dane:\n1. Dane z pliku 'dane.txt'\n2. Dane z klawiatury\n> ";
    int wybor;
    cin >> wybor;

    switch (wybor)
    {
    case 1:
    {
        //---------------------------> Wczytywanie z pliku <---------------------------
        fstream plik;
        plik.open("dane.txt", ios::in);
        if (!plik.good())
        {
            cout << "Blad przy wczytywaniu pliku!" << endl;
            return 1;
        }

        plik >> ile_pol >> ile_browarow >> ile_karczm >> ile_skrzyzowan >> ile_krawedzi;

        //vector pol
        vector<Pole> pola;
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

        for (int i = 0; i < ile_pol; i++)
        {
            int x_, y_;
            int jeczmien_;
            plik >> x_ >> y_ >> jeczmien_;
            pola.emplace_back(x_, y_, jeczmien_);
            macierz_sasiedztwa_zboze[ile_skrzyzowan][i] = jeczmien_;
            macierz_sasiedztwa[ile_skrzyzowan][i] += jeczmien_;
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
            koszty_napraw[y_][x_] = -naprawa_; //krawedzie odwrotne maja koszt naprawy odwrotny

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
        break;
    }
    case 2:
    {
        //---------------------------> Wczytywanie z klawiatury <---------------------------

        //ile jest pol/browarow/karczm/skrzyzowan/krawedzi
        cout << "Podaj ilosc pol:\n> ";
        cin >> ile_pol;
        cout << "Podaj ilosc browarow:\n> ";
        cin >> ile_browarow;
        cout << "Podaj ilosc karczm:\n> ";
        cin >> ile_karczm;
        cout << "Podaj ilosc skrzyzowan:\n> ";
        cin >> ile_skrzyzowan;
        cout << "Podaj ilosc krawedzi:\n> ";
        cin >> ile_krawedzi;

        //vector pol
        vector<Pole> pola;
        //vector browarow
        vector<Browar> browary;
        //vector karczm
        vector<Karczma> karczmy;
        //vector krawedzi
        vector<Krawedz> krawedzie;

        //ile pol w macierzy sasiedztwa
        ile = ile_skrzyzowan + 2;
        //macierz sasiedztwa wypelniona zerami
        vector<vector<int>> macierz_sasiedztwa_zboze(ile, vector<int>(ile, 0));
        vector<vector<int>> macierz_sasiedztwa_piwo(ile, vector<int>(ile, 0));
        macierz_sasiedztwa.resize(ile, vector<int>(ile, 0));
        koszty_napraw.resize(ile, vector<int>(ile, 0));

        cout << "Podaj wspolrzedne pola i ile jeczmienia moga wyprodukowac poszczegolne pola:" << endl;
        for (int i = 0; i < ile_pol; i++)
        {
            cout << "> ";
            int x_, y_;
            int jeczmien_;
            cin >> x_ >> y_ >> jeczmien_;
            pola.emplace_back(x_, y_, jeczmien_);
            macierz_sasiedztwa_zboze[ile_skrzyzowan][i] = jeczmien_;
            macierz_sasiedztwa[ile_skrzyzowan][i] += jeczmien_;
            cout << endl;
        }

        cout << "Podaj wspolrzedne browaru i ile jeczmienia moga przetworzyc poszczegolne browary:" << endl;
        for (int i = 0; i < ile_browarow; i++)
        {
            cout << "> ";
            int x_, y_;
            int przetworzenie_;
            cin >> x_ >> y_ >> przetworzenie_;
            browary.emplace_back(x_, y_, przetworzenie_);
            cout << endl;
        }

        cout << "Podaj wspolrzedne i jakie jest zapotrzebowanie poszczegolnych karczm na piwo:" << endl;
        for (int i = 0; i < ile_karczm; i++)
        {
            cout << "> ";
            int x_, y_;
            int zapotrzebowanie_;
            cin >> x_ >> y_ >> zapotrzebowanie_;
            karczmy.emplace_back(x_, y_, zapotrzebowanie_);
            macierz_sasiedztwa_piwo[ile_skrzyzowan - ile_karczm + i][ile - 1] = zapotrzebowanie_;
            macierz_sasiedztwa[ile_skrzyzowan - ile_karczm + i][ile - 1] += zapotrzebowanie_;
            cout << endl;
        }

        cout << "Podaj krawedzie (w postaci: od do ilosc_jeczmienia ilosc_piwa koszt_naprawy):" << endl;;
        for (int i = 0; i < ile_krawedzi; i++)
        {
            cout << i << "> ";
            int x_;
            int y_;
            int naprawa_;
            int przepustowosc_zboze_;
            int przepustowosc_piwo_;
            cin >> x_ >> y_ >> przepustowosc_zboze_ >> przepustowosc_piwo_ >> naprawa_;
            krawedzie.emplace_back(x_, y_, przepustowosc_zboze_, przepustowosc_piwo_, naprawa_);
            macierz_sasiedztwa_zboze[x_][y_] = przepustowosc_zboze_;
            macierz_sasiedztwa_piwo[x_][y_] = przepustowosc_piwo_;
            koszty_napraw[x_][y_] = naprawa_;  //przydzielamy koszt naprawy dla kazdej krawedzi
            koszty_napraw[y_][x_] = -naprawa_; //krawedzie odwrotne maja koszt naprawy odwrotny
            cout << endl;

            if (przepustowosc_piwo_ == 0)
            {
                macierz_sasiedztwa[x_][y_] += przepustowosc_zboze_;
            }
            else
            {
                macierz_sasiedztwa[x_][y_] += przepustowosc_piwo_;
            }
        }
        break;
    }
    default:
        cout << "Nieprawidlowa opcja!" << endl;
    }

    //-----------------------------> Drukowanie macierzy <-----------------------------

    //macierz kosztow naprawy drog
    drukujMacierz(koszty_napraw, "Macierz kosztow naprawy drog:");

    //macierz sasiedztwa zborza
    drukujMacierz(macierz_sasiedztwa_zboze, "Macierz sasiedztwa (zboze):");
  
    //macierz sasiedztwa piwa
    drukujMacierz(macierz_sasiedztwa_piwo, "Macierz sasiedztwa (piwo):");

    //macierz sasiedztwa wszystko razem
    drukujMacierz(macierz_sasiedztwa, "Macierz sasiedztwa (wszystko razem):");

    pair<int, int> przeplywIkoszt = minCostMaxFlow(macierz_sasiedztwa, koszty_napraw, ile - 2, ile - 1);

    cout << "Maksymalny przeplyw piwa do karczm:        " << przeplywIkoszt.first << " sztuk browarow." << endl;
    cout << "Minimalny koszt naprawy drog do przeplywu: " << przeplywIkoszt.second << " sztuk zlota." << endl;
    return 0;
}