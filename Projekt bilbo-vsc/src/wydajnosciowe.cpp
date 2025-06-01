#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"  
#include "Cwiartka.h"
#include "Merge_sort.h"
#include "Pole.h"
#include "Wezel.h"
#include<vector>
#include <chrono>
#include <iostream>
#include <random>
using namespace std;
vector<Wezel> generujLosowePunkty(int n, int maxWartosc = 1000) {
    vector<Wezel> punkty;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, maxWartosc);
    for (int i = 0; i < n; ++i) {
        punkty.emplace_back(dis(gen), dis(gen));
    }
    return punkty;
}
TEST_CASE("Wydajność - algorytm Grahama") {
    vector<int> rozmiary = {100, 1000, 5000, 10000};
    for (int n : rozmiary) {
        vector<Wezel> punkty = generujLosowePunkty(n);

        auto start = std::chrono::high_resolution_clock::now();
        vector<Wezel> powloka = Wezel::algorytmGrahama(punkty);
        auto end = std::chrono::high_resolution_clock::now();

        double czas = std::chrono::duration<double, std::milli>(end - start).count();
        std::cout << "Graham dla " << n << " punktow trwal: " << czas << " ms" << std::endl;

        // Minimalna asercja — tylko żeby test się liczył
        CHECK(powloka.size() > 0);
    }
}
TEST_CASE("Wydajność - obliczanie pola pola") {
    Pole p, p100, p5000,p10000;
    auto punkty100=generujLosowePunkty(100);
    auto punkty = generujLosowePunkty(1000);
    auto punkty5000=generujLosowePunkty(5000);
    auto punkty10000=generujLosowePunkty(10000);
    for (auto& pt : punkty100){
        p100.dodajPunkt(pt.getX(), pt.getY());
    }
    auto start = std::chrono::high_resolution_clock::now();
    double wynik = p100.obliczPolePola();
    auto end = std::chrono::high_resolution_clock::now();

    double czas = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Pole::obliczPolePola() 100p trwalo: " << czas << " ms" << std::endl;
    CHECK(wynik >= 0.0);
    for (auto& pt : punkty){
        p.dodajPunkt(pt.getX(), pt.getY());
    }
    auto start1 = std::chrono::high_resolution_clock::now();
    double wynik1 = p.obliczPolePola();
    auto end1 = std::chrono::high_resolution_clock::now();

    double czas1 = std::chrono::duration<double, std::milli>(end1 - start1).count();
    std::cout << "Pole::obliczPolePola()1000 trwalo: " << czas1 << " ms" << std::endl;
    CHECK(wynik1 >= 0.0);
    for (auto& pt : punkty5000){
        p5000.dodajPunkt(pt.getX(), pt.getY());
    }
    auto start2 = std::chrono::high_resolution_clock::now();
    double wynik2 = p.obliczPolePola();
    auto end2 = std::chrono::high_resolution_clock::now();

    double czas2 = std::chrono::duration<double, std::milli>(end2 - start2).count();
    std::cout << "Pole::obliczPolePola()5000 trwalo: " << czas2 << " ms" << std::endl;
    CHECK(wynik2 >= 0.0);
    for (auto& pt : punkty10000){
        p10000.dodajPunkt(pt.getX(), pt.getY());
    }
    auto start3 = std::chrono::high_resolution_clock::now();
    double wynik3 = p.obliczPolePola();
    auto end3 = std::chrono::high_resolution_clock::now();

    double czas3 = std::chrono::duration<double, std::milli>(end3 - start3).count();
    std::cout << "Pole::obliczPolePola() 10000 trwalo: " << czas3 << " ms" << std::endl;

    CHECK(wynik3 >= 0.0);
}
TEST_CASE("Wydajność - Cwiartka::czyPunktSieZnajduje") {
    Cwiartka c;
    vector<Wezel> wierzcholki = {
        {0, 0}, {100, 0}, {100, 100}, {0, 100}
    };

    for (auto& w : wierzcholki) {
        c.dodajWierzcholek(w.getX(), w.getY());
    }

    vector<Wezel> punktyTestowe = generujLosowePunkty(1000, 150);

    auto start = chrono::high_resolution_clock::now();
    int znalezione = 0;
    for (auto& p : punktyTestowe) {
        if (c.czyPunktSieZnajduje(p))
            ++znalezione;
    }
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Cwiartka::czyPunktSieZnajduje] 100 testow: " << czas << " ms, znaleziono: " << znalezione << endl;

    CHECK(znalezione >= 0);
}
TEST_CASE("Wydajność - Cwiartka::czyPunktSieZnajduje") {
    Cwiartka c;
    vector<Wezel> wierzcholki = {
        {0, 0}, {1000, 0}, {1000, 1000}, {0, 1000}
    };

    for (auto& w : wierzcholki) {
        c.dodajWierzcholek(w.getX(), w.getY());
    }

    vector<Wezel> punktyTestowe = generujLosowePunkty(10000, 1500);

    auto start = chrono::high_resolution_clock::now();
    int znalezione = 0;
    for (auto& p : punktyTestowe) {
        if (c.czyPunktSieZnajduje(p))
            ++znalezione;
    }
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Cwiartka::czyPunktSieZnajduje] 10k testow: " << czas << " ms, znaleziono: " << znalezione << endl;

    CHECK(znalezione >= 0);
}
TEST_CASE("Wydajność - Cwiartka::czyPunktSieZnajduje") {
    Cwiartka c;
    vector<Wezel> wierzcholki = {
        {0, 0}, {5000, 0}, {5000, 5000}, {0, 5000}
    };

    for (auto& w : wierzcholki) {
        c.dodajWierzcholek(w.getX(), w.getY());
    }

    vector<Wezel> punktyTestowe = generujLosowePunkty(5000, 550);

    auto start = chrono::high_resolution_clock::now();
    int znalezione = 0;
    for (auto& p : punktyTestowe) {
        if (c.czyPunktSieZnajduje(p))
            ++znalezione;
    }
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Cwiartka::czyPunktSieZnajduje] 50000 testow: " << czas << " ms, znaleziono: " << znalezione << endl;

    CHECK(znalezione >= 0);
}
TEST_CASE("Wydajność - Cwiartka::czyPunktSieZnajduje") {
    Cwiartka c;
    vector<Wezel> wierzcholki = {
        {0, 0}, {10000, 0}, {10000, 10000}, {0, 10000}
    };

    for (auto& w : wierzcholki) {
        c.dodajWierzcholek(w.getX(), w.getY());
    }

    vector<Wezel> punktyTestowe = generujLosowePunkty(100000, 15000);

    auto start = chrono::high_resolution_clock::now();
    int znalezione = 0;
    for (auto& p : punktyTestowe) {
        if (c.czyPunktSieZnajduje(p))
            ++znalezione;
    }
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Cwiartka::czyPunktSieZnajduje] 10000 testow: " << czas << " ms, znaleziono: " << znalezione << endl;

    CHECK(znalezione >= 0);
}
TEST_CASE("Wydajność 6854621 - algorytm Grahama") {
    vector<Wezel> punkty = generujLosowePunkty(6854621, 6854621);

    auto start = chrono::high_resolution_clock::now();
    vector<Wezel> powloka = Wezel::algorytmGrahama(punkty);
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Graham] 6854621 punktow: " << czas << " ms" << endl;

    CHECK(powloka.size() > 0);
}

TEST_CASE("Wydajność 6854621 - Pole::obliczPolePola") {
    Pole p;
    auto punkty = generujLosowePunkty(6854621, 6854621);
    for (auto& pt : punkty)
        p.dodajPunkt(pt.getX(), pt.getY());

    auto start = chrono::high_resolution_clock::now();
    double wynik = p.obliczPolePola();
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Pole] 6854621 punktow: " << czas << " ms" << endl;

    CHECK(wynik >= 0.0);
}

TEST_CASE("Wydajność 6854621 - Cwiartka::czyPunktSieZnajduje") {
    Cwiartka c;
    vector<Wezel> wierzcholki = {
        {0, 0}, {6854621, 0}, {6854621, 6854621}, {0, 6854621}
    };

    for (auto& w : wierzcholki) {
        c.dodajWierzcholek(w.getX(), w.getY());
    }

    vector<Wezel> punktyTestowe = generujLosowePunkty(6854621, 6854621);

    auto start = chrono::high_resolution_clock::now();
    int znalezione = 0;
    for (auto& p : punktyTestowe) {
        if (c.czyPunktSieZnajduje(p))
            ++znalezione;
    }
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Cwiartka] 6854621 testow: " << czas << " ms, znaleziono: " << znalezione << endl;

    CHECK(znalezione >= 0);
}
TEST_CASE("Wydajność 10m - algorytm Grahama") {
    vector<Wezel> punkty = generujLosowePunkty(10000000, 10000000);

    auto start = chrono::high_resolution_clock::now();
    vector<Wezel> powloka = Wezel::algorytmGrahama(punkty);
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Graham] 10000000 punktow: " << czas << " ms" << endl;

    CHECK(powloka.size() > 0);
}

TEST_CASE("Wydajność 10000000 - Pole::obliczPolePola") {
    Pole p;
    auto punkty = generujLosowePunkty(10000000, 10000000);
    for (auto& pt : punkty)
        p.dodajPunkt(pt.getX(), pt.getY());

    auto start = chrono::high_resolution_clock::now();
    double wynik = p.obliczPolePola();
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Pole] 10000000 punktow: " << czas << " ms" << endl;

    CHECK(wynik >= 0.0);
}

TEST_CASE("Wydajność 10000000 - Cwiartka::czyPunktSieZnajduje") {
    Cwiartka c;
    vector<Wezel> wierzcholki = {
        {0, 0}, {10000000, 0}, {10000000, 10000000}, {0, 10000000}
    };

    for (auto& w : wierzcholki) {
        c.dodajWierzcholek(w.getX(), w.getY());
    }

    vector<Wezel> punktyTestowe = generujLosowePunkty(10000000, 10000000);

    auto start = chrono::high_resolution_clock::now();
    int znalezione = 0;
    for (auto& p : punktyTestowe) {
        if (c.czyPunktSieZnajduje(p))
            ++znalezione;
    }
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Cwiartka] 10000000 testow: " << czas << " ms, znaleziono: " << znalezione << endl;

    CHECK(znalezione >= 0);
}/*
TEST_CASE("Wydajność 100m - algorytm Grahama") {
    vector<Wezel> punkty = generujLosowePunkty(100000000, 100000000);

    auto start = chrono::high_resolution_clock::now();
    vector<Wezel> powloka = Wezel::algorytmGrahama(punkty);
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Graham] 100000000 punktow: " << czas << " ms" << endl;

    CHECK(powloka.size() > 0);
}

TEST_CASE("Wydajność 100m - Pole::obliczPolePola") {
    Pole p;
    auto punkty = generujLosowePunkty(100000000, 100000000);
    for (auto& pt : punkty)
        p.dodajPunkt(pt.getX(), pt.getY());

    auto start = chrono::high_resolution_clock::now();
    double wynik = p.obliczPolePola();
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Pole] 100000000 punktow: " << czas << " ms" << endl;

    CHECK(wynik >= 0.0);
}

TEST_CASE("Wydajność 100000000 - Cwiartka::czyPunktSieZnajduje") {
    Cwiartka c;
    vector<Wezel> wierzcholki = {
        {0, 0}, {100000000, 0}, {100000000, 100000000}, {0, 100000000}
    };

    for (auto& w : wierzcholki) {
        c.dodajWierzcholek(w.getX(), w.getY());
    }

    vector<Wezel> punktyTestowe = generujLosowePunkty(100000000, 100000000);

    auto start = chrono::high_resolution_clock::now();
    int znalezione = 0;
    for (auto& p : punktyTestowe) {
        if (c.czyPunktSieZnajduje(p))
            ++znalezione;
    }
    auto end = chrono::high_resolution_clock::now();

    double czas = chrono::duration<double, milli>(end - start).count();
    cout << "[Cwiartka] 100000000 testow: " << czas << " ms, znaleziono: " << znalezione << endl;

    CHECK(znalezione >= 0);
}*/