#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "./tads/HashClosedString.cpp"
#include "./tads/GrafoLaImp.cpp"
#include "./tads/MinHeapDjkImp.cpp"

using namespace std;

int main()
{
    int n;
    int m;
    cin >> n >> m;
    tabla2 t = crearTabla2(n * 2 + 1);
    string desde;
    string hasta;

    string *origen = new string[m + 1];
    string *destino = new string[m + 1];
    int *peso = new int[m + 1];

    GrafoLA* grafo = new GrafoLA(n, m, false, true);
    int proxIndice = 1;

    for (int i = 1; i <= m; i++)
    {
        cin >> origen[i] >> destino[i] >> peso[i];
        if (buscarPuntaje(t, origen[i]) == 0)
    {
        insertar2(t, origen[i], proxIndice);
        proxIndice++;
    }

    if (buscarPuntaje(t, destino[i]) == 0)
    {
        insertar2(t, destino[i], proxIndice);
        proxIndice++;
    }
        int u = buscarPuntaje(t, origen[i]);
        int v = buscarPuntaje(t, destino[i]);
        grafo->insertarArista(u, v, peso[i]);
    }
    cin >> desde >> hasta;

    int indiceOrigen = buscarPuntaje(t, desde);
    int indiceDestino = buscarPuntaje(t, hasta);

    if (indiceOrigen == 0 || indiceDestino == 0) {
        cout << -1 << endl;
        delete[] origen;
        delete[] destino;
        delete[] peso;
        return 0;
    }

    int *costos = new int[n + 1];
    int *vengoDe = new int[n + 1];
    bool *visitados = new bool[n + 1];

    grafo->RellenarVec(costos, vengoDe, visitados, n);
    costos[indiceOrigen] = 0;

    MinHeap *h = new MinHeap(n * n);
    insertarEnHeap(h, indiceOrigen, 0);

    while (!estaVacio(h))
    {
        NodoHeap *nodo = tope(h);
        int verticeActual = nodo->vertice;
        eliminarElem(h);

        if (!visitados[verticeActual])
        {
            visitados[verticeActual] = true;

            ListaAdyLA adyacentes = grafo->obtenerAdyacentes(verticeActual);
            while (adyacentes != NULL)
            {
                int verticeAdy = adyacentes->vertice;
                int pesoAdy = adyacentes->peso;

                if (!visitados[verticeAdy] && costos[verticeActual] != INT_MAX && costos[verticeAdy] > costos[verticeActual] + pesoAdy)
                {
                    costos[verticeAdy] = costos[verticeActual] + pesoAdy;
                    vengoDe[verticeAdy] = verticeActual;
                    insertarEnHeap(h, verticeAdy, costos[verticeAdy]);
                }
                adyacentes = adyacentes->sig;
            }
        }
    }
    delete[] h->array;
    delete h;

    int resultado = costos[indiceDestino];
    cout << (resultado == INT_MAX ? -1 : resultado) << endl;

    delete[] origen;
    delete[] destino;
    delete[] peso;
    delete[] costos;
    delete[] vengoDe;
    delete[] visitados;

    return 0;
}