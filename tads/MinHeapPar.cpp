#ifndef MINHEAPPAR_CPP
#define MINHEAPPAR_CPP

#include <iostream>
using namespace std;

// Basado en el Heap de la clase 4 (clase-04-multiestructura): de máximo a
// mínimo, con un par (prioridad, número).

struct Nodo {
    int prioridad;
    int numero;
};

class MinHeapPar {
private:
    Nodo* datos; 
    int cant;

    int padre(int pos) {
        return pos / 2;
    }

    int hijoIzquierdo(int pos) {
        return pos * 2;
    }

    int hijoDerecho(int pos) {
        return pos * 2 + 1;
    }

    bool menor(const Nodo& a, const Nodo& b) {
        if (a.prioridad != b.prioridad) {
            return a.prioridad < b.prioridad;
        }
        return a.numero < b.numero;
    }

    void intercambiar(int pos1, int pos2) {
        Nodo aux = datos[pos1];
        datos[pos1] = datos[pos2];
        datos[pos2] = aux;
    }

    void flotar(int pos) {
        while (pos > 1 && menor(datos[pos], datos[padre(pos)])) {
            intercambiar(pos, padre(pos));
            pos = padre(pos);
        }
    }

    void hundir(int pos) {
        while (hijoIzquierdo(pos) <= cant) {
            int hijoMenor = hijoIzquierdo(pos);
            if (hijoDerecho(pos) <= cant &&
                menor(datos[hijoDerecho(pos)], datos[hijoIzquierdo(pos)])) {
                hijoMenor = hijoDerecho(pos);
            }
            if (!menor(datos[hijoMenor], datos[pos])) {
                return;
            }
            intercambiar(pos, hijoMenor);
            pos = hijoMenor;
        }
    }

public:
    MinHeapPar(int capacidad) {
        datos = new Nodo[capacidad + 1];
        cant = 0;
    }

    ~MinHeapPar() {
        delete[] datos;
    }

    bool esVacio() {
        return cant == 0;
    }

    void insertar(Nodo nodo) {
        cant++;
        datos[cant] = nodo;
        flotar(cant);
    }

    Nodo EliminarMin() {
        Nodo minimo = datos[1];
        datos[1] = datos[cant];
        cant--;
        if (cant > 0) {
            hundir(1);
        }
        return minimo;
    }
};

#endif