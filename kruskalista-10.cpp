// Minimalne drzewo rozpinające
// Algorytm Kruskala
// Data: 6.04.2014
// (C)2014 mgr Jerzy Wałaszek
//--------------------------------

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

// Definicja obiektu kolejki priorytetowej
//----------------------------------------
struct Edge
{
    int v1, v2, weight;      // Wierzchołki krawędzi, waga krawędzi
};

class Queue
{
private:
    Edge * Heap;
    int hpos;
public:
    Queue ( int n );
    ~Queue( );
    Edge front( );
    void push ( Edge e );
    void pop( );
};

// Definicja obiektu struktury zbiorów rozłącznych
//------------------------------------------------
struct DSNode
{
    int up, rank;
};

class DSStruct
{
private:
    DSNode * Z;
public:
    DSStruct ( int n );
    ~DSStruct( );
    void MakeSet ( int v );
    int FindSet ( int v );
    void UnionSets ( Edge e );
};

// Definicja obiektu minimalnego drzewa rozpinającego
//---------------------------------------------------
struct TNode
{
    TNode * next;
    int v, weight;
};

class MSTree
{
private:
    TNode ** A;            // Tablica list sąsiedztwa
    int Alen;              // Liczba komórek w tablicy
    int weight;            // Waga całego drzewa
public:
    MSTree ( int n );
    ~MSTree( );
    void addEdge ( Edge e );
    void print( );
};

// Definicje metod obiektu Queue
//------------------------------

// Konstruktor - tworzy n elementową tablicę heap na kopiec
//---------------------------------------------------------
Queue::Queue ( int n )
{
    Heap = new Edge [ n ];   // Tworzymy tablicę
    hpos = 0;                // Pozycja w kopcu
}

// Destruktor - usuwa kopiec z pamięci
//------------------------------------
Queue::~Queue( )
{
    delete [ ] Heap;
}

// Zwraca krawędź z początku kopca
//--------------------------------
Edge Queue::front( )
{
    return Heap [ 0 ];
}

// Umieszcza w kopcu nową krawędź i odtwarza strukturę kopca
//----------------------------------------------------------
void Queue::push ( Edge e )
{
    int i, j;

    i = hpos++;              // i ustawiamy na koniec kopca
    j = ( i - 1 ) >> 1;      // Obliczamy pozycję rodzica

    // Szukamy miejsca w kopcu dla e

    while( i && ( Heap [ j ].weight > e.weight ) )
    {
        Heap [ i ] = Heap [ j ];
        i = j;
        j = ( i - 1 ) >> 1;
    }

    Heap [ i ] = e;          // Krawędź e wstawiamy do kopca
}

// Usuwa korzeń z kopca i odtwarza jego strukturę
//-----------------------------------------------
void Queue::pop( )
{
    int i, j;
    Edge e;

    if( hpos )
    {
        e = Heap [ --hpos ];

        i = 0;
        j = 1;

        while( j < hpos )
        {
            if( ( j + 1 < hpos ) && ( Heap [ j + 1 ].weight < Heap [ j ].weight ) ) j++;
            if( e.weight <= Heap [ j ].weight ) break;
            Heap [ i ] = Heap [ j ];
            i = j;
            j = ( j << 1 ) + 1;
        }

        Heap [ i ] = e;
    }
}

// Definicje metod obiektu DSStruct
//---------------------------------

// Konstruktor
DSStruct::DSStruct ( int n )
{
    Z = new DSNode [ n ];    // Tworzymy tablicę dla elementów zbiorów
}

// Destruktor
//-----------
DSStruct::~DSStruct( )
{
    delete [ ] Z;            // Usuwamy tablicę ze zbiorami
}

// Tworzy wpis w tablicy Z
//------------------------
void DSStruct::MakeSet ( int v )
{
    Z [ v ].up   = v;
    Z [ v ].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w którym jest wierzchołek v
//----------------------------------------------------------------
int DSStruct::FindSet ( int v )
{
    if( Z [ v ].up != v ) Z [ v ].up = FindSet ( Z [ v ].up );
    return Z [ v ].up;
}

// Łączy ze sobą zbiory z v i u
//-----------------------------
void DSStruct::UnionSets ( Edge e )
{
    int ru, rv;

    ru = FindSet ( e.v1 );   // Wyznaczamy korzeń drzewa z węzłem u
    rv = FindSet ( e.v2 );   // Wyznaczamy korzeń drzewa z węzłem v
    if( ru != rv )           // Korzenie muszą być różne
    {
        if( Z [ ru ].rank > Z [ rv ].rank ) // Porównujemy rangi drzew
            Z [ rv ].up = ru;    // ru większe, dołączamy rv
        else
        {
            Z [ ru ].up = rv;    // równe lub rv większe, dołączamy ru
            if( Z [ ru ].rank == Z [ rv ].rank ) Z [ rv ].rank++;
        }
    }
}

// Definicje metod obiektu MSTree
//-------------------------------

// Konstruktor - tworzy tablicę pustych list sąsiedztwa
//-----------------------------------------------------
MSTree::MSTree ( int n )
{
    int i;

    A = new TNode * [ n ];   // Tworzymy tablicę dynamiczną
    for( i = 0; i < n; i++ ) A [ i ] = NULL; // i wypełniamy ją pustymi listami
    Alen = n - 1;            // Zapamiętujemy długość tablicy
    weight = 0;              // Zerujemy wagę drzewa
}

// Destruktor - usuwa listy oraz tablicę sąsiedztwa
//-------------------------------------------------
MSTree::~MSTree( )
{
    int i;
    TNode *p, *r;

    for( i = 0; i <= Alen; i++ )
    {
        p = A [ i ];
        while( p )
        {
            r = p;               // Zapamiętujemy wskazanie
            p = p->next;         // Przesuwamy się do następnego elementu listy
            delete r;            // Usuwamy element
        }
    }

    delete [ ] A;            // Usuwamy tablicę list sąsiedztwa
}

// Dodaje krawędź do drzewa
//-------------------------
void MSTree::addEdge ( Edge e )
{
    TNode *p;

    weight += e.weight;      // Do wagi drzewa dodajemy wagę krawędzi
    p = new TNode;           // Tworzymy nowy węzeł
    p->v = e.v2;             // Wierzchołek końcowy
    p->weight = e.weight;    // Waga krawędzi
    p->next = A [ e.v1 ];    // Dodajemy p do listy wierzchołka v1
    A [ e.v1 ] = p;

    p = new TNode;           // To samo dla krawędzi odwrotnej
    p->v = e.v1;             // Wierzchołek końcowy
    p->weight = e.weight;    // Waga krawędzi
    p->next = A [ e.v2 ];    // Dodajemy p do listy wierzchołka v2
    A [ e.v2 ] = p;
}

// Wyświetla zawartość drzewa oraz jego wagę
//------------------------------------------
void MSTree::print( )
{
    int i;
    TNode *p;

    cout << endl;
    for( i = 0; i <= Alen; i++ )
    {
        cout << "Vertex " << i << " - ";
        for( p = A [ i ]; p; p = p->next ) cout << p->v << ":" << p->weight << " ";
        cout << endl;
    }
    cout << endl << endl << "Minimal Spanning Tree Weight = " << weight << endl << endl;
}

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main( )
{
	clock_t start, stop;
	float czas;
   ofstream fout;
    fout.open("lkruskal-30c.txt");
    using namespace std::chrono;
	srand((int) time(0));
    int n=30,m=674;   
	int O[4]={24,53674,90};            // Liczba wierzchołków i krawędzi
    Edge e;
    int i,g,z,x,k=0,a=0;


	    int * los = new int[n];
    	int * tab = new int[n];

    for(int k=0;k<n;k++)
    {
        los[k]=k;
    }
    
    while(i<n)
    {
        g= rand() % n;
        if(los[g]==-1)
        {

        }else {
        	tab[i]=0;
            tab[i] = los[g];
            los[g] =-1;


                    i++;
        }
    }
    for(int k=0;k<n;k++)
    {
        cout<<tab[k]<<"   ";
    }

	 
            while(a<100)
	{

		int * W = new int[m] ;
    	int * X = new int[m];
    	int * Y = new int[m];
		
    for(int i = 0; i < n-1; i++)
    {
        z=tab[i];
        Y[i]=z;
        x=tab[i+1];
        X[i]=x;
        W[i]=(rand() % n)+1;

        k=k+2;
    }
    delete [] los;
    delete [] tab;

    i=10;

    while(k<(675))
    {     
        x=rand() % n;
        z=rand() % n;
        if(x==0 || z==0)
        {

        }else
        {
            W[i]=(rand() % n)+1;
            k=k+2;
            i++;
        }
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    DSStruct Z ( n );        // Struktura zbiorów rozłącznych
    Queue Q ( m );           // Kolejka priorytetowa oparta na kopcu
    MSTree T ( n );          // Minimalne drzewo rozpinające

    for( i = 0; i < n; i++ )
        Z.MakeSet ( i );       // Dla każdego wierzchołka tworzymy osobny zbiór

    for( i = 0; i < m; i++ )
    {
        e.v1=X[i]; e.v2=Y[i]; e.weight=W[i]; // Odczytujemy kolejne krawędzie grafu
        Q.push ( e );          // i umieszczamy je w kolejce priorytetowej
    }

    delete [] W;
    delete [] X;
    delete [] Y;

    for( i = 1; i < n; i++ ) // Pętla wykonuje się n - 1 razy !!!
    {
        do
        {
            e = Q.front( );      // Pobieramy z kolejki krawędź
            Q.pop( );            // Krawędź usuwamy z kolejki
        } while( Z.FindSet ( e.v1 ) == Z.FindSet ( e.v2 ) );
        T.addEdge ( e );       // Dodajemy krawędź do drzewa
        Z.UnionSets ( e );     // Zbiory z wierzchołkami łączymy ze sobą
    }


    T.print( );

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