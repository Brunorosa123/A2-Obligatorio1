#include <cassert>
#include <iostream>


struct NodoHeap
{
    int vertice;
    int peso;
};

struct MinHeap
{
    int capacidad;
    NodoHeap *array;
    int primerolibre;

    MinHeap(int capacidad)
    {
        this->capacidad = capacidad;
        this->array = new NodoHeap[capacidad + 1];
        this->primerolibre = 1;
    }

};

void intercambiar(MinHeap *h, int posPadre, int pos)
{
    NodoHeap aux = h->array[posPadre];
    h->array[posPadre] = h->array[pos];
    h->array[pos] = aux;
}

void flotar(MinHeap *h, int pos)
{
    if (pos > 1)
    {
        int padre = pos / 2;
        if (h->array[pos].peso < h->array[padre].peso)
        {
            intercambiar(h, padre, pos);
            flotar(h, padre);
        }
    }
}

void hundir(MinHeap *h, int pos)
{
    int hijoIzq = pos * 2;
    int hijoDer = pos * 2 + 1;
    int menor = pos;

    if (hijoIzq >= h->primerolibre)
    {
        return;
    }

    if (hijoIzq < h->primerolibre && h->array[hijoIzq].peso < h->array[menor].peso)
    {
        menor = hijoIzq;
    }
    if (hijoDer < h->primerolibre && h->array[hijoDer].peso < h->array[menor].peso)
    {
        menor = hijoDer;
    }
    if (menor != pos)
    {
        intercambiar(h, pos, menor);
        hundir(h, menor);
    }
}

void insertarEnHeap(MinHeap *h, int vertice, int peso)
{
    assert(h->primerolibre <= h->capacidad);

    h->array[h->primerolibre].vertice = vertice;
    h->array[h->primerolibre].peso = peso;
    flotar(h, h->primerolibre);
    h->primerolibre++;
}

NodoHeap *tope(MinHeap *h)
{
    assert(h->primerolibre > 1);
    return &h->array[1];
}

void eliminarElem(MinHeap *h)
{
    assert(h->primerolibre > 1);
    h->array[1] = h->array[h->primerolibre - 1];
    h->primerolibre--;
    hundir(h, 1);
}

bool estaVacio(MinHeap *h)
{
    return h->primerolibre == 1;
}
