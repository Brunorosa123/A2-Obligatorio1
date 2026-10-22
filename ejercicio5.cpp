#include <string>
#include <iostream>
#include "tads/MinHeapPar.cpp"
#include "tads/MFset.cpp"

using namespace std;

int main()
{
    int V, E;
    cin >> V >> E;

    if (V == 1)
    {
        cout << 0 << "\n";
        return 0;
    }

    MinHeapPar *heap = new MinHeapPar(E); 
    MFSet *conjuntos = new MFSet(V);
    int *origen = new int[E];  
    int *destino = new int[E]; 
    long long costoTotal = 0;
    int elegidos = 0; 

    for (int i = 0; i < E; i++)
    { 
        int u, v, w;
        cin >> u >> v >> w;
        origen[i] = u;
        destino[i] = v;

        Nodo nuevo;
        nuevo.prioridad = w;
        nuevo.numero = i;
        heap->insertar(nuevo);
    }

    while (!heap->esVacio() && elegidos < V - 1)
    {
        Nodo actual = heap->EliminarMin();
        int e = actual.numero;
        int u = origen[e];
        int v = destino[e];

        if (conjuntos->unir(u, v))
        {
            costoTotal += actual.prioridad;
            elegidos++;
        }
    }

    if (elegidos == V - 1)
    {
        cout << costoTotal << "\n";
    }
    else
    {
        cout << "imposible\n";
    }

    delete heap;
    delete conjuntos;
    delete[] origen;
    delete[] destino;

    return 0;
}