#ifndef DEKODER_H
#define DEKODER_H

#include <string>
#include <map>
using namespace std;

//struktura do budowy drzewa
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f);
};

//zeby ulatwic porownywanie
struct Compare {
    bool operator()(Node* a, Node* b);
};

class Dekoder {
public:
    //dekompresuje(odczytuje plik)
    void decompress(const string& inputFile, string& output);

private:
    //buduje drzewo
    Node* buildTree(map<char, int>& charMap);

    void insert(Node*& root, const string& path, char ch);

    //usuwa drzewo
    void deleteTree(Node* root);
};

#endif
