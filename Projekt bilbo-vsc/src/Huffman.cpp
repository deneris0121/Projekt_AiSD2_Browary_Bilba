#include "Huffman.h"
#include <fstream>
#include <queue>
#include <bitset>
#include <iostream>

using namespace std;

Node::Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

bool Compare::operator()(Node* a, Node* b) {
    return a->freq > b->freq;
}

Node* Huffman::buildTree(const map<char, int>& charMap) {

    //tworzymy kolejke priorytetowa
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& p : charMap){
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1) {
        //wstawiamy wartosc do lewego wezla
        Node* l = pq.top();
        pq.pop();
        //wstawiamy wartosc do prawego wezla
        Node* r = pq.top(); 
        pq.pop();
        //tworzymy nowy wezel i przypisujemy mu odpowiednie wartosci (w pseudokodzie z)
        Node* merged = new Node('\0', l->freq + r->freq);
        merged->left = l;
        merged->right = r;
        //dodajemy nowy wezel do kolejki priorytetowej
        pq.push(merged);
    }
    return pq.top();
}

void Huffman::buildCodes(Node* root, const string& str, map<char, string>& codes) {
    if (!root) return;
    //przypisanie kodu do znaku
    if (!root->left && !root->right){
        codes[root->ch] = str;
    }
    //idziemy w lewo po drzewie dopisujemy 0 do kodu
    buildCodes(root->left, str + "0", codes);
    //idziemy w prawo po drzewie dopisujemy 1 do kodu
    buildCodes(root->right, str + "1", codes);
}

void Huffman::writeHeader(ofstream& out, const map<char, int>& charMap) {
    out << charMap.size() << '\n';
    for (auto& p : charMap){
        out << static_cast<int>(p.first) << ' ' << p.second << '\n';
    }
}

void Huffman::deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void Huffman::compress(const string& text, const string& outputFile) {

    //tworzymy mape <znak,ilosc>
    map<char, int> charMap;
    for (char ch : text){
        charMap[ch]++;
    }

    //tworzymy drzewo
    Node* root = buildTree(charMap);
    //tworzymy mape kodow
    map<char, string> codes;
    buildCodes(root, "", codes);

    //zaczynamy tworzenie pliku wyjsciowego
    ofstream out(outputFile, ios::binary);
    writeHeader(out, charMap);

    //zastepujemy znaki odpowiednim kodem
    string bitString;
    for (char ch : text){
        bitString += codes[ch];
    }

    size_t bitLength = bitString.size();
    out.write(reinterpret_cast<const char*>(&bitLength), sizeof(bitLength));

    //uzupelniamy az dlugosc bitString bedzie podzielna przez 8 
    while (bitString.size() % 8 != 0){
        bitString += '0';
    }

    //petla przechodzaca po naszym tekscie
    for (size_t i = 0; i < bitString.size(); i += 8) {
        //zamieniamy na reprezentacje binarna 
        bitset<8> byte(bitString.substr(i, 8));
        //zamieniamy ja na znak char (1 bajt)
        char c = static_cast<char>(byte.to_ulong());
        //zapisujemy go do pliku
        out.write(&c, 1);
    }
    out.close();
    deleteTree(root);
}
