#include <iostream>
#include <string>
#include "BoyerMoore.h"
#include "KnuthMorrisPratt.h"
#include "Interface.h"
#include "Dekoder.h"

using namespace std;

int main(int argc, char *argv[]) {


    Interface interface;
    string text;
    string filename = "../Projekt bilbo-vsc/output/wynik.bin";
    Dekoder dekoder;
    dekoder.decompress(filename,text);

    interface.wybor(text,argv[2],atoi(argv[1]));


    return 0;
}
