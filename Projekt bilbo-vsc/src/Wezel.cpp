#include<iostream>
//#include "pch.h"
#include "Wezel.h"
#include "Merge_sort.h"
#include <algorithm>

using namespace std;

Wezel::Wezel(int x_, int y_) : x(x_), y(y_) {}

bool Wezel::operator<(const Wezel& p) const {
    return(y < p.y) || (y == p.y && x < p.x);
}

int Wezel::iloczynWektorowy(const Wezel& O, const Wezel& A, const Wezel& B) {
    return (A.getX() - O.getX()) * (B.getY() - O.getY()) -
        (A.getY() - O.getY()) * (B.getX() - O.getX());
}

vector<Wezel> Wezel::algorytmGrahama(const vector<Wezel>& wezly) {
    if (wezly.size() <= 3) return wezly;

    Wezel start = *min_element(wezly.begin(), wezly.end());
    vector<Wezel> posortowaneWezly = wezly; // kopia do sortowania
    mergeSort(posortowaneWezly, 0, posortowaneWezly.size() - 1, start);

    vector<Wezel> powloka;
    for (const Wezel& p : posortowaneWezly) {
        while (powloka.size() >= 2 && iloczynWektorowy(powloka[powloka.size() - 2], powloka[powloka.size() - 1], p) <= 0) {
            powloka.pop_back();
        }
        powloka.push_back(p);
    }

    return powloka;
}
static double poleTrojkata(const Wezel& a, const Wezel& b, const Wezel& c) {
    return 0.5 * abs((b.getX() - a.getX()) * (c.getY() - a.getY()) - (c.getX() - a.getX()) * (b.getY() - a.getY()));
}
double Wezel::obliczPole(const vector<Wezel>& powloka) {
    double pole = 0.0;
    for (size_t i = 1; i < powloka.size() - 1; i++) {
        pole += poleTrojkata(powloka[0], powloka[i], powloka[i + 1]);
    }
    return pole;

}


