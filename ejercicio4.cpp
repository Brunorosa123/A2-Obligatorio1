#include <string>
#include <iostream>
#include "tads/Graph.cpp"
#include "tads/MinHeapPar.cpp"

using namespace std;

int main()
{
    int V;
    int A;

    cin >> V >> A;

    GrafoLA* grafo = new GrafoLA(V);
    MinHeapPar* heap = new MinHeapPar(V);
    int* grado = new int[V + 1]();  
    int* prioridad = new int[V + 1];
    int* orden = new int[V];         
    int cantOrden = 0;

    for (int i = 1; i <= V; i++) {
        cin >> prioridad[i];
    }

    for (int i = 0; i < A; i++) {
        int u, v;
        cin >> u >> v;
        grafo->agregarArista(u, v);
        grado[v]++;
    }
    for (int i = 1; i <= V; i++) {
        if (grado[i] == 0) {
            Nodo nuevo;
            nuevo.prioridad = prioridad[i];
            nuevo.numero = i;
            heap->insertar(nuevo);
        }
    }

    while (!heap->esVacio()){
        Nodo nodo = heap->EliminarMin();
        orden[cantOrden] = nodo.numero;
        cantOrden++;
        Arista* vecino = grafo->vecinosNodo(nodo.numero);
        while (vecino != NULL) {
            grado[vecino->destino]--;
            if (grado[vecino->destino] == 0) {
                Nodo nuevo;
                nuevo.prioridad = prioridad[vecino->destino];
                nuevo.numero = vecino->destino;
                heap->insertar(nuevo);
            }
            vecino = vecino->sig;
        }
    }

    if (cantOrden == V) {                         
        for (int i = 0; i < V; i++) {
            cout << orden[i] << "\n";
        }
    } else {
        cout << "imposible" << "\n";
    }

    delete grafo;
    delete heap;
    delete[] grado;
    delete[] prioridad;
    delete[] orden;
    return 0;
}