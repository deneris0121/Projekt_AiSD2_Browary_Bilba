#ifndef DEKODER_H
#define DEKODER_H

#include "Huffman.h"
#include <string>
#include <map>
using namespace std;

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
