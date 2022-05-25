#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstring>
using namespace std;

#define INF 9999999

int main() {
    using namespace std::chrono;
    int krawedz,suma;  
    int g,edges,k=0,n,z,x,i=0;
    ofstream fout;
    fout.open("pmacierz-1000.txt");
    n=100;
    edges=n;
    int selected[n];
    int h[4]={2500,5000,7500,9890};
    int W[100][100]={NULL};
    srand((int)time(0));
    int los[10];
    int tab[10];
    int a;

    a=0;
    while(a<100) {

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
            tab[i] = los[g];
            los[g] =-1;
            i++;
        }
    }
    for(int k=0;k<n;k++) {
        cout << tab[k] << "   ";
    }
    for(int i = 0; i < n-1; i++)
    {
        z=tab[i];
        x=tab[i+1];
        W[z][x]=(rand() % n)+1;
        W[x][z]=W[z][x];
        k=k+2;
    }



            suma=0;
            while(k<2500)
            {
                x=rand() % n;
                z=rand() % n;
                if(x==z || W[x][z]!=0)
                {

                }else
                {
                    W[x][z]=(rand() % n)+1;
                    W[z][x]=W[x][z];
                    edges++;
                    k=k+2;
                }
            }
            cout << endl;



            high_resolution_clock::time_point t1 = high_resolution_clock::now();

            memset(selected, false, sizeof(selected)); //wartosc selected ustawiamy na false

            krawedz = 0;

            selected[0] = true; //zaczynamy od wierzchołka 0

            int y;


            while (krawedz < n - 1) {
                //For every vertex in the set S, find the all adjacent vertices
                // , calculate the distance from the vertex selected at step 1.
                // if the vertex is already in the set S, discard it otherwise
                //choose another vertex nearest to selected vertex  at step 1.

                int min = INF;

                g = 0;
                y = 0;

                for (int i = 0; i < n; i++) {
                    if (selected[i]) {
                        for (int j = 0; j < n; j++) {
                            if (!selected[j] && W[i][j] != 0) {  // not in selected and there is an edge
                                if (min > W[i][j]) {
                                    min = W[i][j];
                                    g = i;
                                    y = j;
                                }
                            }
                        }
                    }
                }
                cout<<"Wierzcholek "<<g<<" - "<<y<<" : "<<W[g][y]<<endl;
                suma=suma+W[g][y];
                selected[y] = true;
                krawedz++;

            }
            high_resolution_clock::time_point t2 = high_resolution_clock::now();

            duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

            fout << time_span.count();

            fout << endl;
            a++;
        cout<<"Waga minimalnego drzewa rozpinajacego = "<<suma<<endl;
        }
        fout << endl;
        fout << endl;
        fout << endl;
    return 0;
    }