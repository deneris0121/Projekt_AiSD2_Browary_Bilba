#include "BoyerMoore.h"

using namespace std;

BoyerMoore::BoyerMoore(const string& txt, const string& pattern) : text(txt), pattern(pattern) {}

vector<int> BoyerMoore::buildBadCharTable() {
    const int ALPHABET_SIZE = 256;
    vector<int> badChar(ALPHABET_SIZE, 0);
    for (int i = 0; i < pattern.length(); i++) {
        badChar[(unsigned char)pattern[i]] = i;
    }
    return badChar;
}

vector<int> BoyerMoore::buildGoodSuffixTable() {
    int m = pattern.length();
    vector<int> pi(m+1);
    vector<int> BMNext(m + 1, 0);

    int i = m;
    int b = m + 1;

    pi[i] = b;

    while (i > 0) {
        while (b <= m && pattern[i - 1] != pattern[b - 1]) {
            if (BMNext[b] == 0)
            {
                BMNext[b] = b - i;
            }
            b = pi[b];
        }
        b--;
        i--;
        pi[i] = b;
    }
    
    b = pi[0];

    for (int i = 0; i <= m + 1; ++i) {
        if (BMNext[i] == 0)
            BMNext[i] = b;

        if (i == b)
            b = pi[b];
    }

    return BMNext;
}

vector<int> BoyerMoore::search() {
    vector<int> result;
    //wyznaczamy tablice BMNext i tablice zlych znakow
    vector<int> badChar = buildBadCharTable();
    vector<int> goodSuffix = buildGoodSuffixTable();

    int n = text.length();
    int m = pattern.length();

    //sprawdzamy czy wzorzec ma dlugosc wieksza od zera i mniejsza badz rowna tekstowi
    if (m == 0 || n < m) return result;

    int s = 0; // przesunięcie wzorca
    while (s <= n - m) {
        int j = m - 1;
        //sprawdzamy jak dlugo jes zgodnosc
        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        if (j < 0) {
            result.push_back(s);
            s += goodSuffix[1]; 
        } else {
            int badShift = j - badChar[(unsigned char)text[s + j]];
            int goodShift = goodSuffix[j+1];
            int maks;
            if(badShift>goodShift)
            {
                maks=badShift;
            }
            else{
                maks=goodShift;
            }
            if(maks<1)
            {
                maks=1;
            }
            s += maks;
        }
    }

    return result;
}