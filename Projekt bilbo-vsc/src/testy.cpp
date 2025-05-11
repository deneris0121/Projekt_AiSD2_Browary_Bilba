#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"  
#include "Cwiartka.h"
#include "Merge_sort.h"
#include "Pole.h"
#include "Wezel.h"
#include<vector>
using namespace std;

TEST_CASE("WezelTest - OperatorLessThan") {
    Wezel p1(1, 2);
    Wezel p2(2, 3);
    Wezel p3(2, 2);

    CHECK(p1 < p2);
    CHECK(p1 < p3);
    CHECK_FALSE(p3 < p1);
}
TEST_CASE("WezelTest - IloczynWektorowy") {
    Wezel O(0, 0);
    Wezel A(1, 0);
    Wezel B(0, 1);
    CHECK(Wezel::iloczynWektorowy(O, A, B) == 1);  // Lewoskr�t

    CHECK(Wezel::iloczynWektorowy(O, B, A) == -1); // Prawoskr�t

    CHECK(Wezel::iloczynWektorowy(O, A, A) == 0);  // Punkty na jednej linii
}
TEST_CASE("WezelTest - znajdowanieOtoczki") {
    vector<Wezel> wezly = {
        {0, 0},{1, 1},{0, 2},{2, 2},{2, 0}
    };

    vector<Wezel> wynik = Wezel::algorytmGrahama(wezly);

    // Sprawdzenie, czy wynikowa pow�oka zawiera odpowiednie punkty.
    CHECK(wynik.size() == 4);  // Pow�oka powinna zawiera� 4 punkty
    CHECK(wynik[0].getX() == 0);  // Pierwszy punkt w pow�oce powinien mie� x = 0
    CHECK(wynik[0].getY() == 0);  // Pierwszy punkt w pow�oce powinien mie� y = 0
    CHECK(wynik[1].getX() == 2);  // Drugi punkt w pow�oce powinien mie� x = 2
    CHECK(wynik[1].getY() == 0);  // Drugi punkt w pow�oce powinien mie� y = 0
    CHECK(wynik[2].getX() == 2);  // Trzeci punkt w pow�oce powinien mie� x = 2
    CHECK(wynik[2].getY() == 2);  // Trzeci punkt w pow�oce powinien mie� y = 2
    CHECK(wynik[3].getX() == 0);  // Czwarty punkt w pow�oce powinien mie� x = 0
    CHECK(wynik[3].getY() == 2);
}
TEST_CASE("WezelTest - znajdowanieOtoczki2") {
    vector<Wezel> wezly = {
        {-4, -5},{-3, -2},{5, 3},{7, 5},{4, -1},{6,5},{-5,-4},{5,1}
    };

    vector<Wezel> wynik = Wezel::algorytmGrahama(wezly);

    // Sprawdzenie, czy wynikowa pow�oka zawiera odpowiednie punkty.
    CHECK(wynik.size() == 6);  // Pow�oka powinna zawiera� 4 punkty
    CHECK(wynik[0].getX() == -4);  // Pierwszy punkt w pow�oce powinien mie� x = 0
    CHECK(wynik[0].getY() == -5);  // Pierwszy punkt w pow�oce powinien mie� y = 0
    CHECK(wynik[1].getX() == 4);  // Drugi punkt w pow�oce powinien mie� x = 2
    CHECK(wynik[1].getY() == -1);  // Drugi punkt w pow�oce powinien mie� y = 0
    CHECK(wynik[2].getX() == 7);  // Trzeci punkt w pow�oce powinien mie� x = 2
    CHECK(wynik[2].getY() == 5);  // Trzeci punkt w pow�oce powinien mie� y = 2
    CHECK(wynik[3].getX() == 6);  // Czwarty punkt w pow�oce powinien mie� x = 0
    CHECK(wynik[3].getY() == 5);
    CHECK(wynik[4].getX() == -3);  // Trzeci punkt w pow�oce powinien mie� x = 2
    CHECK(wynik[4].getY() == -2);  // Trzeci punkt w pow�oce powinien mie� y = 2
    CHECK(wynik[5].getX() == -5);  // Czwarty punkt w pow�oce powinien mie� x = 0
    CHECK(wynik[5].getY() == -4);
}
TEST_CASE("WezelTest - obliczPoleTrojkata") {
    vector<Wezel> Trojkat = {
         {0, 0},{10, 1},{14, -5}, //pole 32
    };
    vector<Wezel> wynik = Wezel::algorytmGrahama(Trojkat);
    double pole = Wezel::obliczPole(wynik);
    CHECK(pole == 32);
}

TEST_CASE("WezelTest - MergeSort") {
    vector<Wezel> wezly = {
        {3, 4},{1, 1},{2, 2},{0, 0}
    };

    // Punkt pocz�tkowy do algorytmu Grahama
    Wezel start(0, 0);

    // Sortujemy punkty za pomoc� algorytmu mergeSort
    mergeSort(wezly, 0, wezly.size() - 1, start);

    // Sprawdzamy, czy punkty zosta�y posortowane na podstawie iloczynu wektorowego
    CHECK(wezly[0].getX() == 0);  // Pierwszy punkt powinien mie� x = 0
    CHECK(wezly[0].getY() == 0);  // Pierwszy punkt powinien mie� y = 0

    CHECK(wezly[1].getX() == 1);  // Drugi punkt powinien mie� x = 1
    CHECK(wezly[1].getY() == 1);  // Drugi punkt powinien mie� y = 1

    CHECK(wezly[2].getX() == 2);  // Trzeci punkt powinien mie� x = 2
    CHECK(wezly[2].getY() == 2);  // Trzeci punkt powinien mie� y = 2

    CHECK(wezly[3].getX() == 3);  // Czwarty punkt powinien mie� x = 3
    CHECK(wezly[3].getY() == 4);  // Czwarty punkt powinien mie� y = 4
}
TEST_CASE("CwiartkaTest - obliczaniePolaCwiartki") {
    Cwiartka c;
    c.dodajWierzcholek(1, 0);
    c.dodajWierzcholek(-6, 2);
    c.dodajWierzcholek(-6, 10);
    c.dodajWierzcholek(7, 8);
    c.dodajWierzcholek(4, 1);
    double wynik = c.onliczPoleCwiartki();
    CHECK(wynik == 95);
}
TEST_CASE("PoleTest - obliczanieSredniejPunktow") {
    Pole p;
    p.dodajPunkt(2, 3);
    p.dodajPunkt(5, 11);
    p.dodajPunkt(12, 8);
    p.dodajPunkt(9, 5);
    p.dodajPunkt(5, 5);
    p.dodajPunkt(7, 2);
    p.dodajPunkt(4, 1);
    p.ustawSredniaXY();
    Wezel wynik = p.zwrocPunkty();
    CHECK(wynik.getX() == 6);
    CHECK(wynik.getY() == 5);
}
TEST_CASE("PoleTest - ObliczPolePola") {
    Pole p;
    p.dodajPunkt(2, 3);
    p.dodajPunkt(5, 11);
    p.dodajPunkt(12, 8);
    p.dodajPunkt(9, 5);
    p.dodajPunkt(5, 5);
    p.dodajPunkt(7, 2);
    p.dodajPunkt(4, 1);

    double wynik = p.obliczPolePola();
    CHECK(wynik == 54);
}
TEST_CASE("PoleTest - Oblicziloscjeczmienia") {
    Cwiartka c;
    c.dodajWierzcholek(-4, -5);
    c.dodajWierzcholek(-3, -2);
    c.dodajWierzcholek(5, 3);
    c.dodajWierzcholek(7, 5);
    c.dodajWierzcholek(4, -1);
    c.dodajWierzcholek(6, 5);
    c.dodajWierzcholek(-5, -4);
    c.dodajWierzcholek(5, 1);
    c.ustawWydaj(100);
    Pole p;
    p.dodajPunkt(1,0);
    p.dodajPunkt(1, -2);
    p.dodajPunkt(3, 0);
    p.dodajPunkt(3, 1);
    double wynik=p.obliczCalkowitaWartoscJeczmienia(c);
    p.ustawcalkowita_wartosc_jeczmienia(wynik);
    double wynik2 = p.zwroccalkowita_wartosc_jeczmienia();
    CHECK(abs(wynik - 8.57143) < 0.0001);
    CHECK(wynik == wynik2);
}
TEST_CASE("GeometriaTest - PoleWJednejCwiartce") {
    vector<Cwiartka> c;
    Cwiartka c1;
    c1.ustawWydaj(100);
    c1.dodajWierzcholek(0, 0);
    c1.dodajWierzcholek(5, 0);
    c1.dodajWierzcholek(5, 5);
    c1.dodajWierzcholek(0, 5);
    c.push_back(c1);

    Pole p;
    p.dodajPunkt(1, 1);
    p.dodajPunkt(2, 1);
    p.dodajPunkt(2, 2);
    p.dodajPunkt(1, 2);

    std::vector<int> wynik = p.znajdzCwiartki(c);

    CHECK(wynik.size() == 1);       // Powinno znale�� jedn� cwiartk�
    CHECK(wynik[0] == 0);           // A dok�adnie cwiartk� nr 0 (czyli c1)
}

TEST_CASE("GeometriaTest - PoleWObuCwiartkach") {
    vector<Cwiartka> c;
    Cwiartka c1, c2;
    c1.ustawWydaj(100);
    c2.ustawWydaj(150);

    // Cwiartka 1: (0,0) do (5,5)
    c1.dodajWierzcholek(0, 0);
    c1.dodajWierzcholek(5, 0);
    c1.dodajWierzcholek(5, 5);
    c1.dodajWierzcholek(0, 5);

    // Cwiartka 2: (5,0) do (10,5)
    c2.dodajWierzcholek(5, 0);
    c2.dodajWierzcholek(10, 0);
    c2.dodajWierzcholek(10, 5);
    c2.dodajWierzcholek(5, 5);

    c.push_back(c1);
    c.push_back(c2);

    Pole p;
    p.dodajPunkt(4, 2);
    p.dodajPunkt(6, 2);
    p.dodajPunkt(6, 4);
    p.dodajPunkt(4, 4);

    std::vector<int> wynik = p.znajdzCwiartki(c);

    CHECK(wynik.size() == 2);         // Powinien si� znale�� w dw�ch cwiartkach
    CHECK(std::find(wynik.begin(), wynik.end(), 0) != wynik.end());  // c1
    CHECK(std::find(wynik.begin(), wynik.end(), 1) != wynik.end());  // c2
}
TEST_CASE("GeometriaTest - PoleWJednejCwiartce2") {
    vector<Cwiartka> c;
    Cwiartka c1;
    c1.ustawWydaj(400);
    c1.dodajWierzcholek(0, 0);
    c1.dodajWierzcholek(-20, 0);
    c1.dodajWierzcholek(-20, 15);
    c1.dodajWierzcholek(0, 15);
    c.push_back(c1);

    Pole p;
    p.dodajPunkt(-15, 5);
    p.dodajPunkt(-10, 15);
    p.dodajPunkt(-5, 10);

    std::vector<int> wynik = p.znajdzCwiartki(c);

    CHECK(wynik.size() == 1);       // Powinno znale�� jedn� cwiartk�
    CHECK(wynik[0] == 0);           // A dok�adnie cwiartk� nr 0 (czyli c1)
}