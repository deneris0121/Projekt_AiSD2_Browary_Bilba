#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../Projekt bilbo-vsc/src/doctest.h"
#include "BoyerMoore.h"
#include "KnuthMorrisPratt.h"

////////////////////////////////////////////////////
//////////Wyszukiwarka Knuth Morris Pratt///////////
///////////////////////////////////////////////////

TEST_CASE("KMP: Wyszukiwanie wzorca 1 elementowego - 1") {
    KnuthMorrisPratt wyszukiwarka("BACDABC","A");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{1, 4});  // A wystepuje na 1 i 4 miejscu tekstu
}

TEST_CASE("KMP: Wyszukiwanie wzorca 1 elementowego - 2") {
    KnuthMorrisPratt wyszukiwarka("aabcdcddck","c");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{3, 5, 8});  // c wystepuje na 3, 5 i 8 miejscu tekstu
}

TEST_CASE("KMP: Czy rozruzia male i duze litery - 1") {
    KnuthMorrisPratt wyszukiwarka("AaAAaBCdaaBAAC","aA");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{1});  // aA wystepuje na 1 miejscu tekstu    
}

TEST_CASE("KMP: Czy rozruzia male i duze litery - 2") {
    KnuthMorrisPratt wyszukiwarka("AAAABCDBC","aA");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{});  // aA nie wystepuje w tekscie wiec zwraca pusty vector 
}


TEST_CASE("KMP: Wzorzec wystepuje na poczatku tekstu") {
    KnuthMorrisPratt wyszukiwarka("ABCDAEEE","ABCD");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{0});  // ABCD wystepuje na 0 miejscu tekstu      
}

TEST_CASE("KMP: Wzorzec wystepuje na koncu tekstu") {
    KnuthMorrisPratt wyszukiwarka("ABCEAEEEABCD","ABCD");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{8});  // ABCD wystepuje na 8 miejscu tekstu      
}

TEST_CASE("KMP: Wzorzec ktory nachodzi na siebie w tekscie") {
    KnuthMorrisPratt wyszukiwarka("XXXZXXXYZXXYZXXYZYXX","XXYZXXY");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{5,9});  // XXYZXXY wystepuje na 5 i 9 miejscu tekstu      
}

TEST_CASE("KMP: Wzorzec dlugosci tekstu - 1") {
    KnuthMorrisPratt wyszukiwarka("XXAXX","XXAXX");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{0});  // XXAXX wystepuje na 0 miejscu tekstu     
}

TEST_CASE("KMP: Wzorzec dlugosci tekstu - 2") {
    KnuthMorrisPratt wyszukiwarka("XXAXY","XXAXX");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{});  // XXAXX nie wystepuje w tekscie
}

TEST_CASE("KMP: Pusty wzorzec") {
    KnuthMorrisPratt wyszukiwarka("XXAXX","");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{});  // nic nie wyszukujemy wiec nic nie znajdzie
}

TEST_CASE("KMP: Wzorzec dluzszy niz tekst") {
    KnuthMorrisPratt wyszukiwarka("123","123456789");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{});  // wzorzec za dlugi wiec nie ma go w tekscie 
}

////////////////////////////////////////////////////
/////////////Wyszukiwarka Boyer Moore//////////////
///////////////////////////////////////////////////

TEST_CASE("BM: Wyszukiwanie wzorca 1 elementowego - 1") {
    BoyerMoore wyszukiwarka("BACDABC","A");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{1, 4});  // A wystepuje na 1 i 4 miejscu tekstu
}

TEST_CASE("BM: Wyszukiwanie wzorca 1 elementowego - 2") {
    BoyerMoore wyszukiwarka("aabcdcddck","c");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{3, 5, 8});  // c wystepuje na 3, 5 i 8 miejscu tekstu
}

TEST_CASE("BM: Czy rozruzia male i duze litery - 1") {
    BoyerMoore wyszukiwarka("AaAAaBCdaaBAAC","aA");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{1});  // aA wystepuje na 1 miejscu tekstu    
}

TEST_CASE("BM: Czy rozruzia male i duze litery - 2") {
    BoyerMoore wyszukiwarka("AAAABCDBC","aA");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{});  // aA nie wystepuje w tekscie wiec zwraca pusty vector 
}


TEST_CASE("BM: Wzorzec wystepuje na poczatku tekstu") {
    BoyerMoore wyszukiwarka("ABCDAEEE","ABCD");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{0});  // ABCD wystepuje na 0 miejscu tekstu      
}

TEST_CASE("BM: Wzorzec wystepuje na koncu tekstu") {
    BoyerMoore wyszukiwarka("ABCEAEEEABCD","ABCD");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{8});  // ABCD wystepuje na 8 miejscu tekstu      
}

TEST_CASE("BM: Wzorzec ktory nachodzi na siebie w tekscie") {
    BoyerMoore wyszukiwarka("XXXZXXXYZXXYZXXYZYXX","XXYZXXY");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{5,9});  // XXYZXXY wystepuje na 5 i 9 miejscu tekstu      
}

TEST_CASE("BM: Wzorzec dlugosci tekstu - 1") {
    BoyerMoore wyszukiwarka("XXAXX","XXAXX");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{0});  // XXAXX wystepuje na 0 miejscu tekstu
}

TEST_CASE("BM: Wzorzec dlugosci tekstu - 2") {
    BoyerMoore wyszukiwarka("XXAXY","XXAXX");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{});  // XXAXX nie wystepuje w tekscie
}

TEST_CASE("BM: Pusty wzorzec") {
    BoyerMoore wyszukiwarka("XXAXX","");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{});  // nic nie wyszukujemy wiec nic nie znajdzie   
}

TEST_CASE("BM: Wzorzec dluzszy niz tekst") {
    BoyerMoore wyszukiwarka("123","123456789");
    vector<int> wyniki = wyszukiwarka.search();
    CHECK(wyniki == vector<int>{});  // wzorzec za dlugi wiec nie ma go w tekscie 
}