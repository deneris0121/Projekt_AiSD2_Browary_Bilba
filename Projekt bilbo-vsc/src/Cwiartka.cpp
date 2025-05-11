#include <vector>          // WA�NE: przed innymi include, bo vector mo�e by� w nag��wku
//#include "pch.h"
#include "Cwiartka.h"
#include "Wezel.h"         // <-- MUSISZ to mie�, by klasa Wezel by�a znana
#include <cmath>
using namespace std;       // lub zamiast tego u�ywaj std::vector

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
Ten algorytm �ledzi, jak "owija si�" linia wok� punktu.Dzia�a to na zasadzie obliczania liczby nawini��(lub zmian orientacji), kt�re tworzy kraw�d� wielok�ta wzgl�dem punktu.

Je�li punkt jest wewn�trz wielok�ta, suma nawini�� wok� punktu wynosi 1 (w sensie liczby pe�nych obrot�w wok� punktu).

Je�li punkt znajduje si� na zewn�trz, suma nawini�� wynosi 0.


*/
bool Cwiartka::czyPunktSieZnajduje(Wezel& p) {
        int n = punkty_Cwiartki.size();
        int windingNumber = 0;

        for (int i = 0; i < n; i++) {
            Wezel a = punkty_Cwiartki[i];
            Wezel b = punkty_Cwiartki[(i + 1) % n];  // Kraw�d� (a, b)

            // Sprawdzamy, czy punkt p le�y na kraw�dzi
            if (punktNaKrawedzi(a, b, p)) {
                return true;  // Punkt le�y na kraw�dzi
            }

            // Je�li punkt jest w obr�bie kraw�dzi, sprawdzamy, w kt�r� stron� si� "zawija"
            if (a.getY() <= p.getY()) {
                if (b.getY() > p.getY()) {
                    // Sprawdzamy orientacj� (czy punkt jest po lewej od kraw�dzi)
                    if ((Wezel::iloczynWektorowy(a, b, p)) > 0)
                        windingNumber++;  // Zwi�kszamy liczb� nawini��
                }
            }
            else {
                if (b.getY() <= p.getY()) {
                    if ((Wezel::iloczynWektorowy(a, b, p)) < 0)
                        windingNumber--;  // Zmniejszamy liczb� nawini��
                }
            }
        }

        // Je�li suma nawini�� wynosi zero, punkt jest na zewn�trz
        return windingNumber != 0;
    }
bool Cwiartka::punktNaKrawedzi(Wezel& a, Wezel& b, Wezel& p) {
    /* Sprawdzamy, czy punkt p le�y na kraw�dzi(a, b)
     Punkt p le�y na kraw�dzi, je�li:
     - jest w obr�bie zakresu kraw�dzi
     - le�y na tej samej linii (sprawdzamy orientacj�)
     */

    double crossProduct = (p.getY() - a.getY()) * (b.getX() - a.getX()) - (p.getX() - a.getX()) * (b.getY() - a.getY());
    if (abs(crossProduct) > 1e-9) {  // Zbyt ma�a tolerancja dla dok�adno�ci zmiennoprzecinkowej
        return false;  // Punkt nie le�y na tej samej linii
    }

    // Sprawdzamy, czy punkt p jest w obr�bie odcinka
    if (min(a.getX(), b.getX()) <= p.getX() && p.getX() <= max(a.getX(), b.getX()) &&
        min(a.getY(), b.getY()) <= p.getY() && p.getY() <= max(a.getY(), b.getY())) {
        return true;  // Punkt le�y na kraw�dzi
    }

    return false;
}