#include <cassert>

struct NodoHeap
{
    int costo;
    int vertice;
};

struct MinHeap
{
    int capacidad;
    NodoHeap *array;
    int primerolibre;
};

typedef MinHeap *MinHeapPtr;

static int padreH(int pos) { return pos / 2; }
static int hijoIzqH(int pos) { return pos * 2; }
static int hijoDerH(int pos) { return pos * 2 + 1; }

MinHeapPtr crearHeap(int capacidad)
{
    MinHeapPtr h = new MinHeap;
    h->capacidad = capacidad;
    h->array = new NodoHeap[capacidad + 1];
    h->primerolibre = 1;
    return h;
}

static bool menorPrioridad(NodoHeap n1, NodoHeap n2)
{
    return n1.costo < n2.costo;
}

static void intercambiarH(MinHeapPtr h, int a, int b)
{
    NodoHeap aux = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = aux;
}

static void flotar(MinHeapPtr h, int pos)
{
    if (pos > 1)
    {
        int p = padreH(pos);
        if (menorPrioridad(h->array[pos], h->array[p]))
        {
            intercambiarH(h, pos, p);
            flotar(h, p);
        }
    }
}

static void hundir(MinHeapPtr h, int pos)
{
    int izq = hijoIzqH(pos);
    int der = hijoDerH(pos);
    if (izq >= h->primerolibre)
        return;

    int menorHijo = izq;
    if (der < h->primerolibre && menorPrioridad(h->array[der], h->array[izq]))
        menorHijo = der;

    if (menorPrioridad(h->array[menorHijo], h->array[pos]))
    {
        intercambiarH(h, pos, menorHijo);
        hundir(h, menorHijo);
    }
}

void insertarHeap(NodoHeap nodo, MinHeapPtr h)
{
    assert(h->primerolibre <= h->capacidad);

    h->array[h->primerolibre] = nodo;
    flotar(h, h->primerolibre);
    h->primerolibre++;
}

NodoHeap extraerMin(MinHeapPtr h)
{
    assert(h->primerolibre > 1);
    
    NodoHeap minimo = h->array[1];
    h->array[1] = h->array[h->primerolibre - 1];
    h->primerolibre--;
    if (h->primerolibre > 1)
        hundir(h, 1);
    return minimo;
}

bool heapVacio(MinHeapPtr h)
{
    return h->primerolibre == 1;
}

void destruirHeap(MinHeapPtr h)
{
    delete[] h->array;
    delete h;
}
