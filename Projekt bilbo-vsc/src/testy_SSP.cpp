#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FordFulkerson.h"
#include "Graf.h"
#include <vector>

// Testy Dijkstry z potencjalami

TEST_CASE("Dijkstra: Minimalny przeplyw, jedna sciezka") {
    vector<vector<int>> graf = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty_n = {
        {0, 2, 0, 0, 0},
        {-2, 0, 3, 0, 0},
        {0, -3, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    vector<int> koszty_d(graf.size());
    vector<int> potencjaly(graf.size(), 0);
    int source = 3;
    int target = 4;

    CHECK(Dijkstra(graf, koszty_n, rodzic, koszty_d, potencjaly, source, target) == true);
    CHECK(rodzic[target] == 2);
    CHECK(rodzic[2] == 1);
    CHECK(rodzic[1] == 0);
    CHECK(rodzic[0] == source);
    CHECK(rodzic[source] == -1);

    CHECK(koszty_d[target] == 5);
    CHECK(koszty_d[2] == 5);
    CHECK(koszty_d[1] == 2);
    CHECK(koszty_d[0] == 0);
    CHECK(koszty_d[source] == 0);
}

TEST_CASE("Dijkstra: Brak polaczenia karczmy z target") {
    vector<vector<int>> graf = {
        {0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 3, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty_n = {
        {0, 0, 0, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0},
        {0, -2, 0, 2, 2, 0, 0, 0, 0},
        {-2, 0, -2, 0, 0, 2, 0, 0, 0},
        {0, 0, -2, 0, 0, 2, 2, 0, 0},
        {0, 0, 0, -2, -2, 0, 0, 0, 0},
        {0, 0, 0, 0, -2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    vector<int> koszty_d(graf.size());
    vector<int> potencjaly(graf.size(), 0);
    int source = 7;
    int target = 8;

    CHECK(Dijkstra(graf, koszty_n, rodzic, koszty_d, potencjaly, source, target) == false);
    CHECK(rodzic[target] == NULL);
    CHECK(rodzic[6] == 4);
    CHECK(rodzic[4] == 2);
    CHECK(rodzic[2] == 1);

    CHECK(rodzic[5] == 3);
    CHECK(rodzic[3] == 0);

    CHECK(koszty_d[target] == INT_MAX);
    CHECK(koszty_d[6] == 6);
    CHECK(koszty_d[5] == 4);
    CHECK(koszty_d[4] == 4);
    CHECK(koszty_d[3] == 2);
    CHECK(koszty_d[2] == 2);
    CHECK(koszty_d[1] == 0);
    CHECK(koszty_d[0] == 0);
    CHECK(koszty_d[source] == 0);
}

TEST_CASE("Dijkstra: Graf zawierajacy cykl + rozne przepustowosci") {
    vector<vector<int>> graf = {
        {0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 0, 0, 0},
        {0, 0, 6, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 3, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty_n = {
        {0, 0, 6, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 5, 2, 0, 0, 0, 0, 0, 0},
        {-6, -5, 0, -1, 8, 0, 0, 0, 0, 0},
        {0, -2, 1, 0, -3, 0, 0, 0, 0, 0},
        {0, 0, -8, 3, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, -7, 0, 10, 4, 0, 0},
        {0, 0, 0, 0, 0, -10, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, -4, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    vector<int> koszty_d(graf.size());
    vector<int> potencjaly(graf.size(), 0);
    int source = 8;
    int target = 9;

    CHECK(Dijkstra(graf, koszty_n, rodzic, koszty_d, potencjaly, source, target) == true);
    CHECK(rodzic[target] == 7);
    CHECK(rodzic[7] == 5);
    CHECK(rodzic[6] == 5);
    CHECK(rodzic[5] == 4);
    CHECK(rodzic[4] == 2);
    CHECK(rodzic[2] == 3);
    CHECK(rodzic[3] == 1);

    CHECK(koszty_d[target] == 22);
    CHECK(koszty_d[7] == 22);
    CHECK(koszty_d[6] == 28);
    CHECK(koszty_d[5] == 18);
    CHECK(koszty_d[4] == 11);
    CHECK(koszty_d[3] == 2);
    CHECK(koszty_d[2] == 3);
}

TEST_CASE("Dijkstra: Graf z krawedziami odwrotnymi, iteracja inna niz pierwsza") {
    vector<vector<int>> graf = {
        {0, 0, 3, 1, 0, 0, 4, 0},
        {0, 0, 0, 6, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0},
        {4, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 4, 0, 0, 0, 4},
        {0, 0, 0, 2, 0, 0, 0, 2},
        {0, 5, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0}
    };
    vector<vector<int>> koszty_n = {
        {0, 0, 8, 3, 0, 0, 0, 0},
        {0, 0, 0, 6, 0, 0, 0, 0},
        {-8, 0, 0, 0, 3, 0, 0, 0},
        {-3, -6, 0, 0, 4, -9, 0, 0},
        {0, 0, -3, -4, 0, 0, 0, 0},
        {0, 0, 0, 9, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    vector<int> koszty_d(graf.size());
    vector<int> potencjaly = {0, 0, 8, 3, 7, INT_MAX, 0, 7};
    int source = 6;
    int target = 7;

    CHECK(Dijkstra(graf, koszty_n, rodzic, koszty_d, potencjaly, source, target) == true);
    CHECK(rodzic[target] == 4);
    CHECK(rodzic[5] == NULL);
    CHECK(rodzic[4] == 3);
    CHECK(rodzic[3] == 1);
    CHECK(rodzic[2] == 0);
    CHECK(rodzic[0] == 3);

    CHECK(koszty_d[target] == 3);
    CHECK(koszty_d[5] == INT_MAX);
    CHECK(koszty_d[4] == 3);
    CHECK(koszty_d[2] == 3);
    CHECK(koszty_d[0] == 3);
    CHECK(koszty_d[3] == 3);
    CHECK(koszty_d[1] == 0);
}

TEST_CASE("Dijkstra: Uzycie krawedzi odwrotnej do znalezienia sciezki") {
    vector<vector<int>> graf = {
        {0, 0, 3, 1, 0, 0, 4, 0},
        {0, 0, 0, 3, 0, 0, 3, 0},
        {0, 0, 0, 0, 4, 0, 0, 0},
        {4, 3, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 7, 0, 0, 0, 1},
        {0, 0, 0, 2, 0, 0, 0, 2},
        {0, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 7, 0, 0, 0}
    };
    vector<vector<int>> koszty_n = {
        {0, 0, 8, 3, 0, 0, 0, 0},
        {0, 0, 0, 6, 0, 0, 0, 0},
        {-8, 0, 0, 0, 3, 0, 0, 0},
        {-3, -6, 0, 0, 4, -9, 0, 0},
        {0, 0, -3, -4, 0, 0, 0, 0},
        {0, 0, 0, 9, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    vector<int> koszty_d(graf.size());
    vector<int> potencjaly = {3, 0, 11, 6, 10, INT_MAX, 0, 10};
    int source = 6;
    int target = 7;

    CHECK(Dijkstra(graf, koszty_n, rodzic, koszty_d, potencjaly, source, target) == true);
    CHECK(rodzic[target] == 4);
    CHECK(rodzic[5] == NULL);
    CHECK(rodzic[4] == 2);
    CHECK(rodzic[3] == 1);
    CHECK(rodzic[2] == 0);
    CHECK(rodzic[0] == 3);

    CHECK(koszty_d[target] == 4);
    CHECK(koszty_d[5] == INT_MAX);
    CHECK(koszty_d[4] == 4);
    CHECK(koszty_d[2] == 0);
    CHECK(koszty_d[0] == 0);
    CHECK(koszty_d[3] == 0);
    CHECK(koszty_d[1] == 0);
}

TEST_CASE("Dijkstra: Wszystkie mozliwe polaczenia w grafie, zerowe koszty") {
    vector<vector<int>> graf = {
        {0, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 1, 0, 0, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0}
    };
    vector<vector<int>> koszty_n = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    vector<int> koszty_d(graf.size());
    vector<int> potencjaly(graf.size(), 0);
    int source = 7;
    int target = 8;

    CHECK(Dijkstra(graf, koszty_n, rodzic, koszty_d, potencjaly, source, target) == true);
    CHECK(rodzic[target] == 5);
    CHECK(rodzic[6] == 2);
    CHECK(rodzic[5] == 2);
    CHECK(rodzic[4] == 0);
    CHECK(rodzic[3] == 0);
    CHECK(rodzic[2] == 0);

    CHECK(koszty_d[target] == 0);
    CHECK(koszty_d[6] == 0);
    CHECK(koszty_d[5] == 0);
    CHECK(koszty_d[4] == 0);
    CHECK(koszty_d[3] == 0);
    CHECK(koszty_d[2] == 0);
}

// Test aktualizacji potencjalow

TEST_CASE("Aktualizowanie potencjalow") {
    int rozmiar = 8;
    vector<int> koszty_d = {0, 0, 2, 0, 0, 7, 0, 7};
    vector<int> potencjaly = {0, 0, 2, 4, 8, 7, 0, 7};

    aktualizacjaPotencjalow(rozmiar, koszty_d, potencjaly);

    CHECK(potencjaly[0] == 0);
    CHECK(potencjaly[1] == 0);
    CHECK(potencjaly[2] == 4);
    CHECK(potencjaly[3] == 4);
    CHECK(potencjaly[4] == 8);
    CHECK(potencjaly[5] == 14);
    CHECK(potencjaly[6] == 0);
    CHECK(potencjaly[7] == 14);
}

// Testy Successive Shortest Path

TEST_CASE("Successive Shortest Path: Przeplyw 1, jedna sciezka") {
    vector<vector<int>> graf = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty = {
        {0, 2, 0, 0, 0},
        {-2, 0, 3, 0, 0},
        {0, -3, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    int source = 3;
    int target = 4;

    int przeplyw = fordFulkerson(graf, source, target);
    pair<int, int> wynik = SSP(graf, koszty, przeplyw, source, target);

    CHECK(wynik.first == przeplyw);
    CHECK(wynik.second == 5);
}

TEST_CASE("SSP: Uzycie krawedzi odwrotnej") {
    vector<vector<int>> graf = {
        {0, 2, 8, 8, 0, 0, 0, 0},
        {0, 0, 0, 9, 0, 0, 0, 0},
        {0, 0, 0, 0, 6, 4, 0, 0},
        {0, 0, 0, 0, 0, 7, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 0, 6, 0, 0, 10},
        {10, 10, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty = {
        {0, 3, 5, 4, 0, 0, 0, 0},
        {-3, 0, 0, 6, 0, 0, 0, 0},
        {-5, 0, 0, 0, 5, 2, 0, 0},
        {-4, -6, 0, 0, 0, 3, 0, 0},
        {0, 0, -5, 0, 0, -7, 0, 0},
        {0, 0, -2, -3, 7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 6;
    int target = 7;

    int przeplyw = fordFulkerson(graf, source, target);
    pair<int, int> wynik = SSP(graf, koszty, przeplyw, source, target);

    CHECK(wynik.first == przeplyw);
    CHECK(wynik.second == 130);
}

TEST_CASE("SSP: Wszystkie mozliwe polaczenia w grafie, zerowe koszty") {
    vector<vector<int>> graf = {
        {0, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 1, 1, 1, 0, 0, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0}
    };
    vector<vector<int>> koszty = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 7;
    int target = 8;

    int przeplyw = fordFulkerson(graf, source, target);
    pair<int, int> wynik = SSP(graf, koszty, przeplyw, source, target);

    CHECK(wynik.first == przeplyw);
    CHECK(wynik.second == 0);
}

TEST_CASE("SSP: Waskie gardlo") {
    vector<vector<int>> graf = {
        {0, 0, 0, 3, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 8, 7, 0, 0, 0},
        {0, 0, 0, 5, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 10, 0, 0},
        {0, 0, 0, 0, 0, 0, 9, 0, 0},
        {0, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 8},
        {6, 4, 9, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty = {
        {0, 0, 0, 7, 4, 0, 0, 0, 0},
        {0, 0, 0, 0, 15, 19, 0, 0, 0},
        {0, 0, 0, 8, 0, 0, 0, 0, 0},
        {-7, 0, -8, 0, 0, 0, 20, 0, 0},
        {-4, -15, 0, 0, 0, 0, 16, 0, 0},
        {0, -19, 0, 0, 0, 0, 6, 0, 0},
        {0, 0, 0, -20, -16, -6, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 7;
    int target = 8;

    int przeplyw = fordFulkerson(graf, source, target);
    pair<int, int> wynik = SSP(graf, koszty, przeplyw, source, target);

    CHECK(wynik.first == przeplyw);
    CHECK(wynik.second == 199);
}

TEST_CASE("SSP: Graf zawierajacy cykl") {
    vector<vector<int>> graf = {
        {0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 8, 0, 0, 0, 0, 0},
        {0, 0, 6, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 4, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
        {3, 4, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty = {
        {0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
        {-4, -2, 0, -6, 8, 0, 0, 0, 0, 0},
        {0, -2, 6, 0, -4, 0, 0, 0, 0, 0},
        {0, 0, -8, 4, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, -7, 0, 4, 2, 0, 0},
        {0, 0, 0, 0, 0, -4, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, -2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 8;
    int target = 9;

    int przeplyw = fordFulkerson(graf, source, target);
    pair<int, int> wynik = SSP(graf, koszty, przeplyw, source, target);

    CHECK(wynik.first == przeplyw);
    CHECK(wynik.second == 134);
}

TEST_CASE("SSP: Brak przeplywu") {
    vector<vector<int>> graf = {
        {0, 0, 2, 6, 0, 0, 0, 0},
        {0, 0, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4},
        {6, 4, 9, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty = {
        {0, 0, 98, 99, 0, 0, 0, 0},
        {0, 0, 0, 97, 0, 0, 0, 0},
        {-98, 0, 0, 0, 96, 0, 0, 0},
        {-99, -97, 0, 0, 95, 0, 0, 0},
        {0, 0, -96, -95, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 6;
    int target = 7;

    int przeplyw = fordFulkerson(graf, source, target);
    pair<int, int> wynik = SSP(graf, koszty, przeplyw, source, target);

    CHECK(wynik.first == przeplyw);
    CHECK(wynik.second == 0);
}

TEST_CASE("SSP: Graf z wielkimi i malymi przepustowosciami") {
    vector<vector<int>> graf = {
        {0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1000, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1000, 0, 0, 1000, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1000},
        {1000, 1000, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty = {
        {0, 0, 1, 0, 900, 0, 0, 0, 0},
        {0, 0, 0, 800, 700, 0, 0, 0, 0},
        {-1, 0, 0, -500, 0, 600, 0, 0, 0},
        {0, -800, 500, 0, 0, 400, 300, 0, 0},
        {-900, -700, 0, 0, 0, 0, 200, 0, 0},
        {0, 0, -600, -400, 0, 0, 0, 0, 0},
        {0, 0, 0, -300, -200, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 7;
    int target = 8;

    int przeplyw = fordFulkerson(graf, source, target);
    pair<int, int> wynik = SSP(graf, koszty, przeplyw, source, target);

    CHECK(wynik.first == przeplyw);
    CHECK(wynik.second == 2601);
}

TEST_CASE("SSP: Wiele zbednych wierzcholkow w grafie") {
    vector<vector<int>> graf = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<vector<int>> koszty = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, -1000, 0, 10000, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, -10000, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 11;
    int target = 12;

    int przeplyw = fordFulkerson(graf, source, target);
    pair<int, int> wynik = SSP(graf, koszty, przeplyw, source, target);

    CHECK(wynik.first == przeplyw);
    CHECK(wynik.second == 44000);
}