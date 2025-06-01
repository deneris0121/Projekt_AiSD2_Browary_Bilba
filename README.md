# Projekt_AiSD2_Browary_Bilba
Projekt na Algorytmy i struktury danych 2. Opisujący łańcuch dostaw i produkcji piwa 
Wymagania:
    Python 3.8+
    Flask (pip install flask)
    Kompilator C++ (np. g++)
Przed uruchomieniem aplikacji webowej, należy skompilować program główny oraz program wyszukiwarka napisane w C++. W katalogu "Projekt bilbo-vsc/src" projektu wykonaj:
    g++ main.cpp Calosc.cpp Browar.cpp Cwiartka.cpp FordFulkerson.cpp Graf.cpp Karczma.cpp Krawedz.cpp Merge_sort.cpp Pole.cpp Wezel.cpp Drukuj.cpp Zapis.cpp Huffman.cpp -o program.exe
W katalogu "Wyszukiwarka" projektu wykonaj:
    g++ main.cpp BoyerMoore.cpp KnuthMorrisPratt.cpp Interface.cpp Dekoder.cpp -o wyszukiwarka.exe
uruchom aplikacje webową:
    app.py
Po uruchomieniu w przeglądarce wejdź na adres:
    http://127.0.0.1:5000

Struktura projektu:
├──.vscode/
├── projekt bilbo-vsc/              # Pliki źródłowe C++
├── raporty testow/                 # Raporty testów jednostkowych
├── strona_html/                    # strony html i style
├── Wyszukiwarka/                   # Pliki żródłowe C++ 
├── app.py                          # Flask 
├── blad/dane2/elo .txt             # dane wejsciowe z pliku
├── dokumentacja                    # dokumentacja projektu
└── README.md                       # Ten plik