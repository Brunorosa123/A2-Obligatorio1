#ifndef MINHEAP_CPP
#define MINHEAP_CPP

#include <iostream>
using namespace std;
// Basado en 01_minheap.cpp de la clase 3 (clase-03-heap-main), con long long.

class MinHeap {
private:
    long long* datos;     
    int cantidad;
    int capacidad;

    int padre(int pos) {
        return pos / 2;
    }

    int hijoIzquierdo(int pos) {
        return 2 * pos;
    }

    int hijoDerecho(int pos) {
        return 2 * pos + 1;
    }

    void intercambiar(int pos1, int pos2) {
        long long aux = datos[pos1];
        datos[pos1] = datos[pos2];
        datos[pos2] = aux;
    }

    void flotar(int pos) {
        while (pos > 1 && datos[pos] < datos[padre(pos)]) {
            intercambiar(pos, padre(pos));
            pos = padre(pos);
        }
    }

    void hundir(int pos) {
        while (hijoIzquierdo(pos) <= cantidad) {

            int hijoMenor = hijoIzquierdo(pos);

            if (hijoDerecho(pos) <= cantidad &&
                datos[hijoDerecho(pos)] < datos[hijoIzquierdo(pos)]) {

                hijoMenor = hijoDerecho(pos);
            }

            if (datos[pos] <= datos[hijoMenor]) {
                return;
            }

            intercambiar(pos, hijoMenor);
            pos = hijoMenor;
        }
    }

public:
    MinHeap(int capacidad) {
        this->capacidad = capacidad;
        this->cantidad = 0;
        this->datos = new long long[capacidad + 1];  
    }

    ~MinHeap() {
        delete[] datos;
    }

    bool esVacio() {
        return cantidad == 0;
    }

    int tamanio() {
        return cantidad;
    }

    void insertar(long long valor) {
        if (cantidad == capacidad) {
            return;
        }

        cantidad++;
        datos[cantidad] = valor;
        flotar(cantidad);
    }

    long long obtenerMinimo() {
        if (esVacio()) {
            cout << "Error: el heap esta vacio" << endl;
            return -1;
        }

        return datos[1];
    }

    long long eliminarMinimo() {
        if (esVacio()) {
            cout << "Error: el heap esta vacio" << endl;
            return -1;
        }

        long long minimo = datos[1];

        datos[1] = datos[cantidad];
        cantidad--;

        if (cantidad > 0) {
            hundir(1);
        }

        return minimo;
    }
};

#endif
