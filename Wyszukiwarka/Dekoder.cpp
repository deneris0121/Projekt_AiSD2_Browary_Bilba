#include "Dekoder.h"
#include <fstream>
#include <bitset>
#include <queue>
#include <iostream>

using namespace std;

Node::Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

bool Compare::operator()(Node* a, Node* b) {
    return a->freq > b->freq;
}

Node* Dekoder::buildTree(map<char, int>& charMap) {

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

void Dekoder::deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void Dekoder::decompress(const string& inputFile, string& output) {
    ifstream file(inputFile, ios::binary);
    if (!file.is_open()) {
        cout << "Nie mozna otworzyc pliku: " << inputFile << endl;
        exit(0);
    }

    int ile;
    file >> ile;
    //file.get(); // pomijamy '\n'

    //tworzymy mape <znak,ile>
    map<char, int> charMap;
    for (int i = 0; i < ile; ++i) {
        int znak, freq;
        file >> znak >> freq;
        file.get(); // pomijamy '\n'
        //dodajemy element do mapy
        charMap[static_cast<char>(znak)] = freq;
    }

    Node* root = buildTree(charMap);

    //czytamy dlugosc pliku przed dodaniem 0
    /*int bitLength;
    file >> bitLength;
    file.get(); // pomijamy '\n'*/
    size_t bitLength;
    file.read(reinterpret_cast<char*>(&bitLength), sizeof(bitLength));

    //odczytujemy zakodowana zawartosc i zapisujemy do bitString
    string bitString;
    char byte;
    while (file.read(&byte, 1)) {
        bitset<8> bits(static_cast<char>(byte));
        bitString += bits.to_string();
    }
    file.close();

    bitString = bitString.substr(0, bitLength); // usuwamy niepotrzebne znaki

    Node* current = root;
    for (char bit : bitString) {
        //przechodzimy po drzewie zeby zdekodowac 
        if (bit == '0'){
            current = current->left;
        } 
        else{
            current = current->right;
        }

        if (!current->left && !current->right) {
            //zapisujemy poprawna litere
            output = output + current->ch;
            current = root;
        }
    }

    deleteTree(root);
}
