#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
using namespace std;

#define V 10
int parent[V];

// Find set of vertex i
int find(int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Does union of i and j. It returns
// false if i and j are already in same
// set.
void union1(int i, int j)
{
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

// Finds MST using Kruskal's algorithm
void kruskalMST(int W[V][V])
{
    int mincost = 0; // Cost of min MST.

    // Initialize sets of disjoint sets.
    for (int i = 0; i < V; i++)
        parent[i] = i;

    // Include minimum weight edges one by one
    int edge_count = 0;
    while (edge_count < V - 1) {
        int min = INT_MAX, a = 0, b = 0;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (find(i) != find(j) && W[i][j] < min && W[i][j]!=0) {
                    min = W[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        union1(a, b);
        cout<<"Wierzcholek "<<a<<" - "<<b<<" : "<<min<<endl;
        edge_count++;
        mincost += min;
    }
    printf("\n Minimum cost= %d \n", mincost);
}


int main() {
    using namespace std::chrono;
    int g,edges,a,n,z,ka=0,k,x,i=0;
    n=10;
    edges=n*(n-1);
    float o[4]={};
    float h[4] = {1220, 2450, 3700, 4900};
    for(int i = 0;i<4;i++)
    {
        o[i]=edges*h[i];
        cout<<o[i]<<endl;
    }
    o[0]=o[0]-0.5;
    o[2]=o[2]-0.5;

    ofstream fout;
    fout.open("kmacierz-700.txt");
    int X[10][10]={NULL};
    srand((int)time(0));
    int * los = new int[n];
    int * tab = new int[n];
    a = 0;
    while (a < 100) {

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

    for(int i = 0; i < n-1; i++)
    {
        z=tab[i];
        x=tab[i+1];
        X[z][x]=(rand() % n)+1;
        X[x][z]=X[z][x];
        ka=ka+2;
    }
    k=ka;






        while (k < 27) {
            x = rand() % n;
            z = rand() % n;
            if (x == z || X[x][z] != 0) {

            } else {
                X[x][z] = (rand() % n) + 1;
                X[z][x] = X[x][z];
                k = k + 2;
            }
        }
        cout << endl;

        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        kruskalMST(X);

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

        fout << time_span.count();

        fout << endl;
        a++;
    }
    fout << endl;
    fout << endl;
    fout << endl;


    delete [] los;
    delete [] tab;
    fout.close();
    return 0;
}