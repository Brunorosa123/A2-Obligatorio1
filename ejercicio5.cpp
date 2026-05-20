#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "./tads/GrafoLaImp.cpp"

using namespace std;

bool dfs(GrafoLA *grafo, int vertice, int colorAct, int *colores)
{
    colores[vertice] = colorAct;

    ListaAdyLA ady = grafo->obtenerAdyacentes(vertice);

    while (ady != NULL)
    {
        int dest = ady->vertice;

        if (colores[dest] == -1)
        {
            if (!dfs(grafo, dest, 1 - colorAct, colores))
            {
                return false;
            }
        }
        else if (colores[dest] == colorAct)
        {
            return false;
        }

        ady = ady->sig;
    }

    return true;
}

int main()
{
    int V;
    int A;

    cin >> V >> A;

    GrafoLA *grafo = new GrafoLA(V, A, false, false);

    for (int i = 0; i < A; i++)
    {
        int u;
        int v;

        cin >> u >> v;

        grafo->insertarArista(u, v, 1);
    }

    int *colores = new int[V + 1];

    for (int i = 1; i <= V; i++)
    {
        colores[i] = -1;
    }

    bool Bipartito = true;

    for (int i = 1; i <= V; i++)
    {
        if (colores[i] == -1)
        {
            if (!dfs(grafo, i, 0, colores))
            {
                Bipartito = false;
                break;
            }
        }
    }

    if (Bipartito)
    {
        cout << "SI" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    delete[] colores;

    return 0;
}