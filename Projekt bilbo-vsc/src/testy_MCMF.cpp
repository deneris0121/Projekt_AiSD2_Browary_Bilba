#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
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

// Testy MinCostMaxFlow

TEST_CASE("MinCostMaxFlow: Uzycie krawedzi odwrotnej + pozniejszy cykl") {
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

    pair<int, int> wynik = minCostMaxFlow(graf, koszty, source, target);

    CHECK(wynik.first == 15);
    CHECK(wynik.second == 130);
}