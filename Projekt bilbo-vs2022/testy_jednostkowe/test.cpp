#include "pch.h"
#include "../Projekt bilbo/Pole.h"
#include "../Projekt bilbo/Merge_sort.h"
using namespace std;

TEST(PoleTest, KonstruktorDomyslny) {
    Pole p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PoleTest, KonstruktorParametryczny) {
    Pole p(3, 7, 100);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), 7);
}

TEST(PoleTest, OperatorLessThan) {
    Pole p1(1, 2, 10);
    Pole p2(2, 3, 20);
    Pole p3(2, 2, 30);

    EXPECT_TRUE(p1 < p2);
    EXPECT_TRUE(p1 < p3);
    EXPECT_FALSE(p3 < p1);
}

TEST(PoleTest, IloczynWektorowy) {
    Pole O(0, 0, 0);
    Pole A(1, 0, 0);
    Pole B(0, 1, 0);
    EXPECT_EQ(Pole::iloczynWektorowy(O, A, B), 1);  // Lewoskrêt

    EXPECT_EQ(Pole::iloczynWektorowy(O, B, A), -1); // Prawoskrêt

    EXPECT_EQ(Pole::iloczynWektorowy(O, A, A), 0);  // Punkty na jednej linii
}


TEST(PoleTest, AlgorytmGrahama) {
    vector<Pole> wezly = {
        Pole(0, 0, 10),
        Pole(1, 1, 15),
        Pole(0, 2, 20),
        Pole(2, 2, 30),
        Pole(2, 0, 40)
    };

    vector<Pole> wynik = Pole::algorytmGrahama(wezly);

    // Sprawdzenie, czy wynikowa pow³oka zawiera odpowiednie punkty.
    EXPECT_EQ(wynik.size(), 4);  // Pow³oka powinna zawieraæ 4 punkty
    EXPECT_EQ(wynik[0].getX(), 0);  // Pierwszy punkt w pow³oce powinien mieæ x = 0
    EXPECT_EQ(wynik[0].getY(), 0);  // Pierwszy punkt w pow³oce powinien mieæ y = 0
    EXPECT_EQ(wynik[1].getX(), 2);  // Drugi punkt w pow³oce powinien mieæ x = 2
    EXPECT_EQ(wynik[1].getY(), 0);  // Drugi punkt w pow³oce powinien mieæ y = 0
    EXPECT_EQ(wynik[2].getX(), 2);  // Trzeci punkt w pow³oce powinien mieæ x = 2
    EXPECT_EQ(wynik[2].getY(), 2);  // Trzeci punkt w pow³oce powinien mieæ y = 2
    EXPECT_EQ(wynik[3].getX(), 0);  // Czwarty punkt w pow³oce powinien mieæ x = 0
    EXPECT_EQ(wynik[3].getY(), 2);  // Czwarty punkt w pow³oce powinien mieæ y = 2
}
TEST(PoleTest, MergeSort) {
    vector<Pole> wezly = {
        Pole(3, 4, 0),
        Pole(1, 1, 0),
        Pole(2, 2, 0),
        Pole(0, 0, 0)
    };

    // Punkt pocz¹tkowy do algorytmu Grahama
    Pole start(0, 0, 0);

    // Sortujemy punkty za pomoc¹ algorytmu mergeSort
    mergeSort(wezly, 0, wezly.size() - 1, start);

    // Sprawdzamy, czy punkty zosta³y posortowane na podstawie iloczynu wektorowego
    EXPECT_EQ(wezly[0].getX(), 0);  // Pierwszy punkt powinien mieæ x = 0
    EXPECT_EQ(wezly[0].getY(), 0);  // Pierwszy punkt powinien mieæ y = 0

    EXPECT_EQ(wezly[1].getX(), 1);  // Drugi punkt powinien mieæ x = 1
    EXPECT_EQ(wezly[1].getY(), 1);  // Drugi punkt powinien mieæ y = 1

    EXPECT_EQ(wezly[2].getX(), 2);  // Trzeci punkt powinien mieæ x = 2
    EXPECT_EQ(wezly[2].getY(), 2);  // Trzeci punkt powinien mieæ y = 2

    EXPECT_EQ(wezly[3].getX(), 3);  // Czwarty punkt powinien mieæ x = 3
    EXPECT_EQ(wezly[3].getY(), 4);  // Czwarty punkt powinien mieæ y = 4
}