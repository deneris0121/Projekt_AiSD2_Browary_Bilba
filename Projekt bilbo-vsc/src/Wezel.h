#ifndef WEZEL_H
#define WEZEL_H
#include <vector>
using namespace std;
class Wezel
{
protected:
    //polozenie wezla
    int x, y;
public:
    Wezel(int x_, int y_);
    int getX() const { return x; }
    int getY() const { return y; }
    bool operator<(const Wezel& p) const;
    static int iloczynWektorowy(const Wezel& O, const Wezel& A, const Wezel& B);
    static vector <Wezel> algorytmGrahama(const vector<Wezel>& punkty);
    static double obliczPole(const vector<Wezel>& powloka);

}; 
#endif
