#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
using namespace std;

struct Edge
{
    int v1, v2, weight;
};

class Kolejka
{
private:
    Edge * Heap;
    int hp;
public:
    Kolejka ( int n );
    ~Kolejka( );
    Edge front( );
    void push ( Edge e );
    void pop( );
};


struct TNode
{
    TNode * next;
    int v, weight;
};

class Drzewo
{
private:
    TNode ** A;                  // Tablica list sąsiedztwa
    int tablen;                    // Liczba komórek w tablicy
    int weight;                  // Waga całego drzewa
public:
    Drzewo ( int n );
    ~Drzewo( );
    void addEdge ( Edge e );
    TNode * getAList ( int n );
    void print( );
};

// Definicje metod obiektu Kolejka
//------------------------------

// Konstruktor - tworzy n elementową tablicę heap na kopiec
//---------------------------------------------------------
Kolejka::Kolejka ( int n )
{
    Heap = new Edge [ n ];         // Tworzymy tablicę
    hp = 0;                      // Pozycja w kopcu
}

// Destruktor - usuwa kopiec z pamięci
//------------------------------------
Kolejka::~Kolejka( )
{
    delete [ ] Heap;
}

// Zwraca krawędź z początku kopca
//--------------------------------
Edge Kolejka::front( )
{
    return Heap [ 0 ];
}

// Umieszcza w kopcu nową krawędź i odtwarza strukturę kopca
//----------------------------------------------------------
void Kolejka::push ( Edge e )
{
    int i, j;

    i = hp++;                    // i ustawiamy na koniec kopca
    j = ( i - 1 ) >> 1;            // Obliczamy pozycję rodzica

    // Szukamy miejsca w kopcu dla e

    while( i && ( Heap [ j ].weight > e.weight ) )
    {
        Heap [ i ] = Heap [ j ];
        i = j;
        j = ( i - 1 ) >> 1;
    }

    Heap [ i ] = e;                // Krawędź e wstawiamy do kopca
}

// Usuwa korzeń z kopca i odtwarza jego strukturę
//-----------------------------------------------
void Kolejka::pop( )
{
    int i, j;
    Edge e;

    if( hp )
    {
        e = Heap [ --hp ];

        i = 0;
        j = 1;

        while( j < hp )
        {
            if( ( j + 1 < hp ) && ( Heap [ j + 1 ].weight < Heap [ j ].weight ) ) j++;
            if( e.weight <= Heap [ j ].weight ) break;
            Heap [ i ] = Heap [ j ];
            i = j;
            j = ( j << 1 ) + 1;
        }

        Heap [ i ] = e;
    }
}

// Definicje metod obiektu Drzewo
//-------------------------------

// Konstruktor - tworzy tablicę pustych list sąsiedztwa
//-----------------------------------------------------
Drzewo::Drzewo ( int n )
{
    int i;

    A = new TNode * [ n ];         // Tworzymy tablicę dynamiczną
    for( i = 0; i < n; i++ ) A [ i ] = NULL; // i wypełniamy ją pustymi listami
    tablen = n - 1;                  // Zapamiętujemy długość tablicy
    weight = 0;                    // Zerujemy wagę drzewa
}

// Destruktor - usuwa listy oraz tablicę sąsiedztwa
//-------------------------------------------------
Drzewo::~Drzewo( )
{
    int i;
    TNode *p, *r;

    for( i = 0; i <= tablen; i++ )
    {
        p = A [ i ];
        while( p )
        {
            r = p;                     // Zapamiętujemy wskazanie
            p = p->next;               // Przesuwamy się do następnego elementu listy
            delete r;                  // Usuwamy element
        }
    }

    delete [ ] A;                  // Usuwamy tablicę list sąsiedztwa
}

// Dodaje krawędź do drzewa
//-------------------------
void Drzewo::addEdge ( Edge e )
{
    TNode *p;

    weight += e.weight;            // Do wagi drzewa dodajemy wagę krawędzi
    p = new TNode;                 // Tworzymy nowy węzeł
    p->v = e.v2;                   // Wierzchołek końcowy
    p->weight = e.weight;          // Waga krawędzi
    p->next = A [ e.v1 ];          // Dodajemy p do listy wierzchołka v1
    A [ e.v1 ] = p;

    p = new TNode;                 // To samo dla krawędzi odwrotnej
    p->v = e.v1;                   // Wierzchołek końcowy
    p->weight = e.weight;          // Waga krawędzi
    p->next = A [ e.v2 ];          // Dodajemy p do listy wierzchołka v2
    A [ e.v2 ] = p;
}

// Zwraca wskaźnik początku listy sąsiadów wierzchołka
//----------------------------------------------------
TNode * Drzewo::getAList ( int n )
{
    return A [ n ];
}

// Wyświetla zawartość drzewa oraz jego wagę
//------------------------------------------
void Drzewo::print( )
{
    int i;
    TNode *p;

    cout << endl;
    for( i = 0; i <= tablen; i++ )
    {
        cout << "Wierzcholek " << i << " - ";
        for( p = A [ i ]; p; p = p->next ) cout << p->v << ":" << p->weight << " ";
        cout << endl;
    }
    cout << endl << endl << "Waga minimalnego drzewa rozpinajacego = " << weight << endl << endl;
}

int main( )
{
    TNode * p;
    ofstream fout;
    fout.open("lprim.txt");
    using namespace std::chrono;
    srand((int) time(0));
    int n=100,m;
    int h[4]={2500,5000,7500,9900};
    Edge e;
    int i,g,v,r,z,x,k,a=0;




    int W[10000]={};
    int Y[10000]={};
    int X[10000]={};


    m=h[3];
    a=0;
    while(a<100)
    {
        int * los = new int[n];
        int * tab = new int[n];
        for(int k=0;k<n;k++)
        {
            los[k]=k;
        }
        r=0;
        while(r<n)
        {
            g= rand() % n;
            if(los[g]==-1)
            {

            }else {

                tab[r] = los[g];
                los[g] =-1;


                r++;
            }
        }
        for(int k=0;k<n;k++)
        {
            cout<<tab[k]<<"   ";
        }


        k=0;
        for(int i = 0; i < n-1; i++)
        {
            z=tab[i];
            Y[i]=z;
            x=tab[i+1];
            X[i]=x;
            W[i]=(rand() % n)+1;
            k=k+2;
        }
        i=100;
        cout<<i;
        delete [] los;
        delete [] tab;

        while(k<m)
        {
            x=rand() % n;
            X[i]=x;
            z=rand() % n;
            Y[i]=z;

            W[i]=(rand() % n)+1;
            k=k+2;
            i++;

        }

        high_resolution_clock::time_point t1 = high_resolution_clock::now();


        Kolejka Q ( m );
        Drzewo T ( n );
        Drzewo G ( n );
        bool * visited = new bool [ n ];

        for( i = 0; i < n; i++ )
            visited [ i ] = false;      // tablicę odwiedzin

        for(int i = 0; i < m; i++ )
        {
            e.v1=X[i]; e.v2=Y[i]; e.weight=W[i];
            G.addEdge ( e );
        }

        v = 0;                         // wierzchołek startowy
        visited [ v ] = true;

        for( i = 1; i < n; i++ )
        {
            for( p = G.getAList ( v ); p; p = p->next ) // Przeglądamy listę sąsiadów
                if( !visited [ p->v ] )    // Jeśli sąsiad jest nieodwiedzony,
                {
                    e.v1 = v;                // to tworzymy krawędź
                    e.v2 = p->v;
                    e.weight = p->weight;
                    Q.push ( e );            // Dodajemy ją do kolejki priorytetowej
                }
            do
            {
                e = Q.front( );            // Pobieramy krawędź z kolejki
                Q.pop( );
            } while( visited [ e.v2 ] ); // Krawędź prowadzi poza drzewo?

            T.addEdge ( e );             // Dodajemy krawędź do drzewa rozpinającego
            visited [ e.v2 ] = true;     // Oznaczamy drugi wierzchołek jako odwiedzony
            v = e.v2;
        }

        T.print( );

        delete [ ] visited;

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

        fout << time_span.count();
        fout << endl;

        a++;
    }
    fout << endl;
    fout << endl;
    fout << endl;

    fout.close();

    return 0;
}