#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Huffman.h"
#include "Dekoder.h"
#include <cstdio>
#include <filesystem>

TEST_CASE("Kompresja i dekompresja prostego tekstu") {
    string tekst = "ALA MA KOTA";
    string plik = "../output/test.bin";

    Huffman k;
    k.compress(tekst, plik);

    Dekoder d;
    string wynik;
    // Sprawdzenie, czy plik istnieje
    CHECK_MESSAGE(filesystem::exists(plik), "Plik binarny nie zostal zapisany przez kompresor!");
    d.decompress(plik,wynik);

    CHECK(wynik == tekst);

    // Sprzątanie testowego pliku
    remove("../output/test.bin");
}

TEST_CASE("Kompresja i dekompresja zlozonego tekstu") {
    string tekst = "ALA MA KOTA\nala ma kota.\tAle ma tez psa\n Ktorego bardzo kocha <3\n";
    string plik = "../output/test.bin";

    Huffman k;
    k.compress(tekst, plik);

    Dekoder d;
    string wynik;
    CHECK_MESSAGE(filesystem::exists(plik), "Plik binarny nie zostal zapisany przez kompresor!");
    d.decompress(plik,wynik);

    CHECK(wynik == tekst);

    remove("../output/test.bin");
}

TEST_CASE("Kompresja i dekompresja pustego tekstu") {
    string tekst = "";
    string plik = "../output/test.bin";

    Huffman k;
    k.compress(tekst, plik);

    Dekoder d;
    string wynik;
    CHECK_MESSAGE(filesystem::exists(plik), "Plik binarny nie zostal zapisany przez kompresor!");
    d.decompress(plik,wynik);

    CHECK(wynik == tekst);

    remove("../output/test.bin");
}

TEST_CASE("Kompresja i dekompresja tekstu z powtórzeniami") {
    string tekst = "aaaaabbbbbccccddddaaaa";
    string plik = "../output/test.bin";

    Huffman k;
    k.compress(tekst, plik);

    Dekoder d;
    string wynik;
    CHECK_MESSAGE(filesystem::exists(plik), "Plik binarny nie zostal zapisany przez kompresor!");
    d.decompress(plik,wynik);

    CHECK(wynik == tekst);

    remove("../output/test.bin");
}

TEST_CASE("Kompresja tekstu z jednym znakiem") {
    string tekst = "aaaaaa";
    string plik = "../output/test.bin";

    Huffman k;
    k.compress(tekst, plik);

    Dekoder d;
    string wynik;
    CHECK_MESSAGE(filesystem::exists(plik), "Plik binarny nie zostal zapisany przez kompresor!");
    d.decompress(plik, wynik);

    CHECK(wynik == tekst);

    remove("../output/test.bin");
}

TEST_CASE("Kompresja tekstu z unikalnymi znakami") {
    string tekst = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\t\n";
    string plik = "../output/test.bin";

    Huffman k;
    k.compress(tekst, plik);

    Dekoder d;
    string wynik;
    CHECK_MESSAGE(filesystem::exists(plik), "Plik binarny nie zostal zapisany przez kompresor!");
    d.decompress(plik, wynik);

    CHECK(wynik == tekst);
    remove("../output/test.bin");
}

