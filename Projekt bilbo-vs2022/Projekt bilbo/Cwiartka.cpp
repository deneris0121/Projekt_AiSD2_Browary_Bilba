#include <vector>          // WA¯NE: przed innymi include, bo vector mo¿e byæ w nag³ówku
#include "pch.h"
#include "Cwiartka.h"
#include "Wezel.h"         // <-- MUSISZ to mieæ, by klasa Wezel by³a znana

using namespace std;       // lub zamiast tego u¿ywaj std::vector

Cwiartka::Cwiartka():wydajnosc(0){}

void Cwiartka::ustawWydaj(double w)
{
    wydajnosc = w;
}

void Cwiartka::dodajWierzcholek(int x, int y)
{
    punkty_Cwiartki.emplace_back(x, y);
}

vector<Wezel> Cwiartka::zwrocWierzcholki()
{
    return punkty_Cwiartki;
}

int Cwiartka::zwrocWydajnosc() const
{
    return wydajnosc;
}

double Cwiartka::onliczPoleCwiartki()
{
    vector<Wezel> pag = Wezel::algorytmGrahama(punkty_Cwiartki);
    double wynik = Wezel::obliczPole(pag);
    return wynik;
}
/*algorytm "winding number" 
Ten algorytm œledzi, jak "owija siê" linia wokó³ punktu.Dzia³a to na zasadzie obliczania liczby nawiniêæ(lub zmian orientacji), które tworzy krawêdŸ wielok¹ta wzglêdem punktu.

Jeœli punkt jest wewn¹trz wielok¹ta, suma nawiniêæ wokó³ punktu wynosi 1 (w sensie liczby pe³nych obrotów wokó³ punktu).

Jeœli punkt znajduje siê na zewn¹trz, suma nawiniêæ wynosi 0.


*/
bool Cwiartka::czyPunktSieZnajduje(Wezel& p) {
        int n = punkty_Cwiartki.size();
        int windingNumber = 0;

        for (int i = 0; i < n; i++) {
            Wezel a = punkty_Cwiartki[i];
            Wezel b = punkty_Cwiartki[(i + 1) % n];  // KrawêdŸ (a, b)

            // Sprawdzamy, czy punkt p le¿y na krawêdzi
            if (punktNaKrawedzi(a, b, p)) {
                return true;  // Punkt le¿y na krawêdzi
            }

            // Jeœli punkt jest w obrêbie krawêdzi, sprawdzamy, w któr¹ stronê siê "zawija"
            if (a.getY() <= p.getY()) {
                if (b.getY() > p.getY()) {
                    // Sprawdzamy orientacjê (czy punkt jest po lewej od krawêdzi)
                    if ((Wezel::iloczynWektorowy(a, b, p)) > 0)
                        windingNumber++;  // Zwiêkszamy liczbê nawiniêæ
                }
            }
            else {
                if (b.getY() <= p.getY()) {
                    if ((Wezel::iloczynWektorowy(a, b, p)) < 0)
                        windingNumber--;  // Zmniejszamy liczbê nawiniêæ
                }
            }
        }

        // Jeœli suma nawiniêæ wynosi zero, punkt jest na zewn¹trz
        return windingNumber != 0;
    }
bool Cwiartka::punktNaKrawedzi(Wezel& a, Wezel& b, Wezel& p) {
    /* Sprawdzamy, czy punkt p le¿y na krawêdzi(a, b)
     Punkt p le¿y na krawêdzi, jeœli:
     - jest w obrêbie zakresu krawêdzi
     - le¿y na tej samej linii (sprawdzamy orientacjê)
     */

    double crossProduct = (p.getY() - a.getY()) * (b.getX() - a.getX()) - (p.getX() - a.getX()) * (b.getY() - a.getY());
    if (abs(crossProduct) > 1e-9) {  // Zbyt ma³a tolerancja dla dok³adnoœci zmiennoprzecinkowej
        return false;  // Punkt nie le¿y na tej samej linii
    }

    // Sprawdzamy, czy punkt p jest w obrêbie odcinka
    if (min(a.getX(), b.getX()) <= p.getX() && p.getX() <= max(a.getX(), b.getX()) &&
        min(a.getY(), b.getY()) <= p.getY() && p.getY() <= max(a.getY(), b.getY())) {
        return true;  // Punkt le¿y na krawêdzi
    }

    return false;
}