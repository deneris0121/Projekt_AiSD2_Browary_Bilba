#include "KnuthMorrisPratt.h"

using namespace std;

KnuthMorrisPratt::KnuthMorrisPratt(const string& txt, const string& pattern) : text(txt), pattern(pattern) {}

vector<int> KnuthMorrisPratt::buildPrefixTable() {
    int m = pattern.length();
    vector<int> prefixTable(m);
    prefixTable[0] = 0;
    int k = 0;

    for (int i = 1; i < m; ++i) {
        while (k > 0 && pattern[k] != pattern[i])
            k = prefixTable[k - 1];

        if (pattern[k] == pattern[i])
            ++k;

        prefixTable[i] = k;
    }
    return prefixTable;
}

vector<int> KnuthMorrisPratt::search(){
    vector<int> result;

    //sprawdzamy czy wzorzec ma dlugosc wieksza od zera i mniejsza badz rowna tekstowi
    int m = pattern.length();
    int n = text.length();
    if (m == 0 || n < m){
        return result;
    }

    //wyznaczamy tablice prefiksowa
    vector<int> prefixTable = buildPrefixTable();

    int k = 0;

    for (int i = 0; i < n; ++i) {
        while (k > 0 && pattern[k] != text[i])
            k = prefixTable[k - 1];

        if (pattern[k] == text[i])
            ++k;

        if (k == m) {
            result.push_back(i - m + 1);
            k = prefixTable[k - 1];
        }
    }

    return result;
}
