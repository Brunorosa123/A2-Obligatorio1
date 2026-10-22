#ifndef GRAPH_CPP
#define GRAPH_CPP

#include <iostream>
using namespace std;

class Arista {
public:
    int destino;
    Arista* sig;
    Arista(int destino) : destino(destino), sig(NULL) {}
};

class GrafoLA{
    private:
        Arista** listaAdyacencia;
        int n;

    public:
        GrafoLA(int n) {
            this->n = n;
            listaAdyacencia = new Arista*[n + 1];
            for (int i = 0; i <= n; i++) {
                listaAdyacencia[i] = NULL;
            }
        }
          ~GrafoLA() {
        for (int i = 0; i <= this->n; i++) {
            Arista* actual = this->listaAdyacencia[i];
            while (actual != NULL) {
                Arista* borrar = actual;
                actual = actual->sig;
                delete borrar;
            }
        }
        delete[] this->listaAdyacencia;
    }

        void agregarArista(int origen, int destino){
            Arista* nuevaA = new Arista(destino);
            nuevaA->sig = listaAdyacencia[origen];
            listaAdyacencia[origen] = nuevaA;
        }
        
        Arista* vecinosNodo(int nodo) {
        return this->listaAdyacencia[nodo];
    }
    
    };
#endif