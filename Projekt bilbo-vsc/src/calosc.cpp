#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <queue>
using namespace std;

class Wezel
{
    protected:
        //polozenie wezla
        int x,y;
    public:
        Wezel(int x_, int y_) : x(x_), y(y_) {}
};

class Pole : public Wezel
{
    private:
        //ile jeczmienia produkuje
        int jeczmien;
    public:
        Pole(int x_, int y_, int jeczmien_) : Wezel(x_, y_), jeczmien(jeczmien_) {}



        //wyswietl informacje o polu
        void wyswietl_info()
        {
            cout<<"Pole (x: "<<x<<", y: "<<y<<")\nIlosc produkowanego jeczmienia: "<<jeczmien<<endl<<endl;
        }
};

class Browar : public Wezel
{
    private:
        //ile jeczmienia moze przetworzyc browar
        int przetworzenie;
    public:
        Browar(int x_, int y_, int przetworzenie_) : Wezel(x_, y_), przetworzenie(przetworzenie_) {}

        //wyswietl informacje o browarze
        void wyswietl_info()
        {
            cout<<"Browar (x: "<<x<<", y: "<<y<<")\nIle jeczmienia moze przetworzyc: "<<przetworzenie<<endl<<endl;
        }
};

class Karczma : public Wezel
{
    private:
        //zapotrzebowanie na piwo w karczmie
        int zapotrzebowanie;
    public:
        Karczma(int x_, int y_, int zapotrzebowanie_) : Wezel(x_, y_), zapotrzebowanie(zapotrzebowanie_) {}

        //wyswietl informacje o browarze
        void wyswietl_info()
        {
            cout<<"Karczma (x: "<<x<<", y: "<<y<<")\nZapotrzebowanie na piwo: "<<zapotrzebowanie<<endl<<endl;
        }
};

class Krawedz
{
    private:
        //skad/dokad prowadzi droga
        int start, koniec;
        //ile zboza mozna przetransportowac ta droga
        int przepustowosc_zboze;
        //ile piwa mozna przetransportowac ta droga
        int przepustowosc_piwo;
        //ile kosztuje mozliwa naprawa drogi
        int naprawa;
    public:
        Krawedz(int start_, int koniec_, int przepustowosc_zboze_, int przepustowosc_piwo_, int naprawa_) : start(start_), koniec(koniec_), przepustowosc_zboze(przepustowosc_zboze_), przepustowosc_piwo(przepustowosc_piwo_), naprawa(naprawa_) {}

        //wyswietl informacje o drodze
        void wyswietl_info()
        {
            cout<<"Krawedz (od: "<<start<<", do: "<<koniec<<")\nIle zboza mozna przetransportowac: "<<przepustowosc_zboze<<"\nIle piwa mozna przetransportowac: "<<przepustowosc_piwo<<"\nKoszt naprawy drogi: "<<naprawa<<endl<<endl;
        }
};

bool bfs(vector<vector<int>>& graf,int s,int t,vector<int>& rodzic)
{
    int rozmiar_grafu=graf.size();
    vector<bool> odwiedzone(rozmiar_grafu,false); //inicjacja wektora odwiedzone

    //kolejka przechowuje wierzcholki grafu, ktore jeszcze nie zostaly odwiedzone
	queue<int> kolejka;
    odwiedzone[s]=true; //wierzcholek s - odwiedzony
	kolejka.push(s); //wierzcholek s na poczatek kolejki
	rodzic[s]=-1; //nie ma rodzica bo startowy

	while(!kolejka.empty()) //dopoki kolejka nie jest pusta przeszukujemy graf
    {
		int u=kolejka.front(); //wybieramy pierwszy element kolejki
		kolejka.pop();

		for (int i=0;i<rozmiar_grafu;i++) //patrzymy na sasiadow u
        {
			if(odwiedzone[i]==false && graf[u][i]>0) //czy wierzcholek i nie zostal jeszcze odwiedzony i czy istnieje krawedz od u do i
            {
				if(i==t) //jest sciezka do t 
                {
					rodzic[i]=u; //zapisanie sciezki
					return true; //jest sciezka = true
				}
				kolejka.push(i);
				rodzic[i]=u;
				odwiedzone[i]=true;
			}
		}
	}
	return false; //nie ma sciezki = false
}


int fordFulkerson(vector<vector<int>>& graf, int s, int t)
{
    int rozmiar=graf.size();
	vector<vector<int>> grafkopia=graf; //kopia macierzy sasiedztwa
		

	vector<int> rodzic(rozmiar); //tablica do przechowywania sciezki w drzewie bfs

	int maxprzeplyw=0; //maksymalny przeplyw

	while(bfs(grafkopia,s,t,rodzic)) //jak jest sciezka powiekszajaca
    {
		int przepustowosc=1000000;

		for(int i=t;i!=s;i=rodzic[i]) //znajdowanie minimalnej przepustowosci sciezki
        {
			int j=rodzic[i];
			przepustowosc=min(przepustowosc,grafkopia[j][i]);
		}

		for(int i=t;i!=s;i=rodzic[i]) //aktualizowanie przepustowosci na biezaco i dodawanie przeplywu w druga strone
        {
			int j=rodzic[i];
		    grafkopia[j][i]-=przepustowosc;
		    grafkopia[i][j]+=przepustowosc;
           
		}

		maxprzeplyw+=przepustowosc;
	}

	return maxprzeplyw;
}


int main()
{
    cout<<"----------------------> Witaj w Shire! <----------------------"<<endl<<endl;
    int ile;
    int ile_pol, ile_browarow, ile_karczm, ile_skrzyzowan, ile_krawedzi;
    vector<vector<int>> macierz_sasiedztwa_zboze;
    vector<vector<int>> macierz_sasiedztwa_piwo;
    vector<vector<int>> macierz_sasiedztwa;

    cout<<"Wybierz jak chcesz wczytac dane:\n1. Dane z pliku 'dane.txt'\n2. Dane z klawiatury\n> ";
    int wybor;
    cin>>wybor;

    switch(wybor)
    {
        case 1:
        {
            //---------------------------> Wczytywanie z pliku <---------------------------
            fstream plik;
            plik.open("C:/Users/nettr/OneDrive/Pulpit/projekt bilbo/dane.txt",ios::in);
            if(!plik.good())
            {
                cout<<"Blad przy wczytywaniu pliku!"<<endl;
                return 1;
            }

            plik>>ile_pol>>ile_browarow>>ile_karczm>>ile_skrzyzowan>>ile_krawedzi;

            //vector pol
            vector<Pole> pola;
            //vector browarow
            vector<Browar> browary;
            //vector karczm
            vector<Karczma> karczmy;
            //vector krawedzi
            vector<Krawedz> krawedzie;

            //ile pol w macierzy sasiedztwa
            ile=ile_skrzyzowan+2;
            //macierz sasiedztwa wypelniona zerami
            macierz_sasiedztwa_zboze.resize(ile,vector<int>(ile,0));
            macierz_sasiedztwa_piwo.resize(ile,vector<int>(ile,0));
            macierz_sasiedztwa.resize(ile,vector<int>(ile,0));

            for(int i=0;i<ile_pol;i++)
            {
                int x_,y_;
                int jeczmien_;
                plik>>x_>>y_>>jeczmien_;
                pola.emplace_back(x_,y_,jeczmien_);
                macierz_sasiedztwa_zboze[ile_skrzyzowan][i]=jeczmien_;
                macierz_sasiedztwa[ile_skrzyzowan][i]+=jeczmien_;
            }

            for(int i=0;i<ile_browarow;i++)
            {
                int x_,y_;
                int przetworzenie_;
                plik>>x_>>y_>>przetworzenie_;
                browary.emplace_back(x_,y_,przetworzenie_);
            }

            for(int i=0;i<ile_karczm;i++)
            {
                int x_,y_;
                int zapotrzebowanie_;
                plik>>x_>>y_>>zapotrzebowanie_;
                karczmy.emplace_back(x_,y_,zapotrzebowanie_);
                macierz_sasiedztwa_piwo[ile_skrzyzowan-ile_karczm+i][ile-1]=zapotrzebowanie_;
                macierz_sasiedztwa[ile_skrzyzowan-ile_karczm+i][ile-1]+=zapotrzebowanie_;
            }

            for(int i=0;i<ile_krawedzi;i++)
            {
                int x_;
                int y_;
                int naprawa_;
                int przepustowosc_zboze_=0;
                int przepustowosc_piwo_=0;
                plik>>x_>>y_>>przepustowosc_zboze_>>przepustowosc_piwo_>>naprawa_;
                krawedzie.emplace_back(x_,y_,przepustowosc_zboze_,przepustowosc_piwo_,naprawa_);
                macierz_sasiedztwa_zboze[x_][y_]=przepustowosc_zboze_;
                macierz_sasiedztwa_piwo[x_][y_]=przepustowosc_piwo_;
                if(przepustowosc_piwo_==0)
                {
                    macierz_sasiedztwa[x_][y_]+=przepustowosc_zboze_;
                }
                else
                {
                    macierz_sasiedztwa[x_][y_]+=przepustowosc_piwo_;
                }

            }
            plik.close();
            break;
        }
        case 2:
        {
            //---------------------------> Wczytywanie z klawiatury <---------------------------

            //ile jest pol/browarow/karczm/skrzyzowan/krawedzi
            cout<<"Podaj ilosc pol:\n> ";
            cin>>ile_pol;
            cout<<"Podaj ilosc browarow:\n> ";
            cin>>ile_browarow;
            cout<<"Podaj ilosc karczm:\n> ";
            cin>>ile_karczm;
            cout<<"Podaj ilosc skrzyzowan:\n> ";
            cin>>ile_skrzyzowan;
            cout<<"Podaj ilosc krawedzi:\n> ";
            cin>>ile_krawedzi;

            //vector pol
            vector<Pole> pola;
            //vector browarow
            vector<Browar> browary;
            //vector karczm
            vector<Karczma> karczmy;
            //vector krawedzi
            vector<Krawedz> krawedzie;

            //ile pol w macierzy sasiedztwa
            ile=ile_skrzyzowan+2;
            //macierz sasiedztwa wypelniona zerami
            vector<vector<int>> macierz_sasiedztwa_zboze(ile,vector<int>(ile,0));
            vector<vector<int>> macierz_sasiedztwa_piwo(ile,vector<int>(ile,0));
            macierz_sasiedztwa.resize(ile,vector<int>(ile,0));

            cout<<"Podaj wspolrzedne pola i ile jeczmienia moga wyprodukowac poszczegolne pola:"<<endl;
            for(int i=0;i<ile_pol;i++)
            {
                cout<<"> ";
                int x_,y_;
                int jeczmien_;
                cin>>x_>>y_>>jeczmien_;
                pola.emplace_back(x_,y_,jeczmien_);
                macierz_sasiedztwa_zboze[ile_skrzyzowan][i]=jeczmien_;
                macierz_sasiedztwa[ile_skrzyzowan][i]+=jeczmien_;
                cout<<endl;
            }

            cout<<"Podaj wspolrzedne browaru i ile jeczmienia moga przetworzyc poszczegolne browary:"<<endl;
            for(int i=0;i<ile_browarow;i++)
            {
                cout<<"> ";
                int x_,y_;
                int przetworzenie_;
                cin>>x_>>y_>>przetworzenie_;
                browary.emplace_back(x_,y_,przetworzenie_);
                cout<<endl;
            }

            cout<<"Podaj wspolrzedne i jakie jest zapotrzebowanie poszczegolnych karczm na piwo:"<<endl;
            for(int i=0;i<ile_karczm;i++)
            {
                cout<<"> ";
                int x_,y_;
                int zapotrzebowanie_;
                cin>>x_>>y_>>zapotrzebowanie_;
                karczmy.emplace_back(x_,y_,zapotrzebowanie_);
                macierz_sasiedztwa_piwo[ile_skrzyzowan-ile_karczm+i][ile-1]=zapotrzebowanie_;
                macierz_sasiedztwa[ile_skrzyzowan-ile_karczm+i][ile-1]+=zapotrzebowanie_;
                cout<<endl;
            }

            cout<<"Podaj krawedzie (w postaci: od do ilosc_jeczmienia ilosc_piwa koszt_naprawy):"<<endl;;
            for(int i=0;i<ile_krawedzi;i++)
            {
                cout<<i<<"> ";
                int x_;
                int y_;
                int naprawa_;
                int przepustowosc_zboze_;
                int przepustowosc_piwo_;
                cin>>x_>>y_>>przepustowosc_zboze_>>przepustowosc_piwo_>>naprawa_;
                krawedzie.emplace_back(x_,y_,przepustowosc_zboze_,przepustowosc_piwo_,naprawa_);
                macierz_sasiedztwa_zboze[x_][y_]=przepustowosc_zboze_;
                macierz_sasiedztwa_piwo[x_][y_]=przepustowosc_piwo_;
                cout<<endl;
                if(przepustowosc_piwo_==0)
                {
                    macierz_sasiedztwa[x_][y_]+=przepustowosc_zboze_;
                }
                else
                {
                    macierz_sasiedztwa[x_][y_]+=przepustowosc_piwo_;
                }
            }
            break;
        }
        default:
            cout<<"Nieprawidlowa opcja!"<<endl;
    }

    //-----------------------------> Drukowanie macierzy <-----------------------------

    //macierz sasiedztwa zborza
    cout<<"Macierz sasiedztwa (zborze):"<<endl;
    for(int i=0;i<ile;i++)
    {
        for(int j=0;j<ile;j++)
        {
            cout<<setw(5)<<macierz_sasiedztwa_zboze[i][j];
        }
        cout<<endl;
    }

    cout<<endl;

    //macierz sasiedztwa piwa
    cout<<"Macierz sasiedztwa (piwo):"<<endl;
    for(int i=0;i<ile;i++)
    {
        for(int j=0;j<ile;j++)
        {
            cout<<setw(5)<<macierz_sasiedztwa_piwo[i][j];
        }
        cout<<endl;
    }

    cout<<endl;

    //macierz sasiedztwa wszystko razem
    cout<<"Macierz sasiedztwa (wszystko razem):"<<endl;
    for(int i=0;i<ile;i++)
    {
        for(int j=0;j<ile;j++)
        {
            cout<<setw(5)<<macierz_sasiedztwa[i][j];
        }
        cout<<endl;
    }

    cout<<"Maksymalny przeplyw piwa do karczm: "<<fordFulkerson(macierz_sasiedztwa,ile-2,ile-1)<<endl;
    return 0;
}
