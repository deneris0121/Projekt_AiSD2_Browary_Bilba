#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FordFulkerson.h"
#include <vector>

// Testy BFS

TEST_CASE("BFS: Minimalny przeplyw, jedna sciezka") {
    vector<vector<int>> graf = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    int source = 3;
    int target = 4;

    CHECK(bfs(graf, source, target, rodzic) == TRUE);
}

TEST_CASE("BFS: Brak polaczenia z browarem") {
    vector<vector<int>> graf = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    int source = 7;
    int target = 8;

    CHECK(bfs(graf, source, target, rodzic) == FALSE);
}

TEST_CASE("BFS: Brak polaczenia karczmy z target") {
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
    vector<int> rodzic(graf.size());
    int source = 7;
    int target = 8;

    CHECK(bfs(graf, source, target, rodzic) == FALSE);
}

TEST_CASE("BFS: Graf zawierajacy cykl + rozne przepustowosci") {
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
    vector<int> rodzic(graf.size());
    int source = 8;
    int target = 9;

    CHECK(bfs(graf, source, target, rodzic) == TRUE);
}

TEST_CASE("BFS: Graf z krawedziami odwrotnymi") {
    vector<vector<int>> graf = {
        {0, 0, 3, 1, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0},
        {4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 4},
        {0, 0, 0, 2, 0, 0, 0, 2},
        {3, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    vector<int> rodzic(graf.size());
    int source = 6;
    int target = 7;

    CHECK(bfs(graf, source, target, rodzic) == TRUE);
}

// Testy Forda-Fulkersona

TEST_CASE("FordFulkerson: Przeplyw 1, jedna sciezka") {
    vector<vector<int>> graf = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    int source = 3;
    int target = 4;

    CHECK(fordFulkerson(graf, source, target) == 1);
}

TEST_CASE("FordFulkerson: Graf bardziej zlozony, bez uzywania krawedzi odwrotnych") {
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
    int source = 6;
    int target = 7;

    CHECK(fordFulkerson(graf, source, target) == 15);
}

TEST_CASE("FordFulkerson: Polaczenia kazdego wierzcholka z kazdym") {
    vector<vector<int>> graf = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    int source = 7;
    int target = 8;

    CHECK(fordFulkerson(graf, source, target) == 8);
}

TEST_CASE("FordFulkerson: Waskie gardlo") {
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
    int source = 7;
    int target = 8;

    CHECK(fordFulkerson(graf, source, target) == 8);
}

TEST_CASE("FordFulkerson: Graf uzywajacy krawedzi odwrotnej w szukaniu sciezki") {
    vector<vector<int>> graf = {
        {0, 0, 8, 4, 0, 0, 0, 0},
        {0, 0, 9, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0},
        {0, 0, 0, 0, 10, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 10},
        {0, 0, 0, 0, 0, 0, 0, 10},
        {10, 10, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 6;
    int target = 7;

    CHECK(fordFulkerson(graf, source, target) == 12);
}

TEST_CASE("FordFulkerson: Graf zawierajacy cykl") {
    vector<vector<int>> graf = {
        {0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 8, 0, 0, 0, 0, 0},
        {0, 0, 6, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 4, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int source = 8;
    int target = 9;

    CHECK(fordFulkerson(graf, source, target) == 6);
}

TEST_CASE("FordFulkerson: Brak przeplywu") {
    vector<vector<int>> graf = {
        {0, 0, 2, 6, 0, 0, 0, 0},
        {0, 0, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {6, 4, 9, 0, 0, 0, 0, 0}
    };
    int source = 6;
    int target = 7;
    
    CHECK(fordFulkerson(graf, source, target) == 0);
}

TEST_CASE("FordFulkerson: Graf z wielkimi i malymi przepustwosciami") {
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
    int source = 7;
    int target = 8;

    CHECK(fordFulkerson(graf, source, target) == 3);
}

TEST_CASE("FordFulkerson: Wiele zbednych wierzcholkow w grafie") {
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
    int source = 11;
    int target = 12;

    CHECK(fordFulkerson(graf, source, target) == 4);
}

/*
    Szablon na graf z samymi zerami    

    vector<vector<int>> graf = {
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
*/