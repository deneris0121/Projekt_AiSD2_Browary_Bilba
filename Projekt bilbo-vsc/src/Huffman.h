#ifndef HUFFMAN_H
#define HUFFMAN_H
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

class Huffman {
public:
    //tworzy skompresowany plik
    void compress(const string& text, const string& outputFile);

private:

    //buduje drzewo
    Node* buildTree(const map<char, int>& charMap);
    
    //buduje mape <znak, kod> (dopasowuje danemu znaku odpiwedni ciag 0 i 1) 
    void buildCodes(Node* root, const string& str, map<char, string>& codes);

    //pisze naglowek pliku potrzebny do dekodowania pozniej
    void writeHeader(ofstream& out, const map<char, int>& charMap);

    //usuwa drzewo
    void deleteTree(Node* root);
};

#endif