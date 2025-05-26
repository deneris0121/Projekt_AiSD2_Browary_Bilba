#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graf.h"
#include <vector>

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
/*
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
}*/