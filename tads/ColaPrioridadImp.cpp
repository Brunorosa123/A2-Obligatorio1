#include "ColaPrioridad.h"

struct NodoCola
{
    int orden;
    int Pac;
    int Urg;
    int Hora;
};

struct ColaPrioridad
{
    int capacidad;
    NodoCola *array;
    int primerolibre;
};

typedef ColaPrioridad *ColaPrio;

int padre(int pos) { return pos / 2; }
int hijoizq(int pos) { return pos * 2; }
int hijoder(int pos) { return pos * 2 + 1; }

ColaPrioridad *crearCola(int capacidad)
{
    ColaPrio cp = new ColaPrioridad;
    cp->capacidad = capacidad;
    cp->array = new NodoCola[capacidad + 1];
    cp->primerolibre = 1;
    return cp;
}

bool mayorPrioridad(NodoCola n1, NodoCola n2)
{
    if (n1.Urg > n2.Urg)
        return true;
    if (n1.Urg == n2.Urg)
    {
        if (n1.Hora < n2.Hora)
            return true;
        if (n1.Hora == n2.Hora)
        {
            if (n1.orden < n2.orden)
                return true;
        }
        return false;
    }
        return false;
}

void intercambiar(ColaPrio cp, int a, int b)
{
    NodoCola aux = cp->array[a];
    cp->array[a] = cp->array[b];
    cp->array[b] = aux;
}

void flotar(ColaPrio cp, int pos)
{
    if (pos > 1)
    {
        int p = padre(pos);
        if (mayorPrioridad(cp->array[pos], cp->array[p]))
        {
            intercambiar(cp, pos, p);
            flotar(cp, p);
        }
    }
}

void hundir(ColaPrio cp, int pos)
{
    int izq = hijoizq(pos);
    int der = hijoder(pos);
    if (izq >= cp->primerolibre)
        return;

    int menorhijo = izq;

    if (der < cp->primerolibre && mayorPrioridad(cp->array[der], cp->array[izq]))
    {
        menorhijo = der;
    }
    if (mayorPrioridad(cp->array[menorhijo], cp->array[pos]))
    {
        intercambiar(cp, pos, menorhijo);
        hundir(cp, menorhijo);
    }
}

void insertar(NodoCola nodo, ColaPrio cp)
{
    assert(cp->primerolibre <= cp->capacidad);
    cp->array[cp->primerolibre] = nodo;
    flotar(cp, cp->primerolibre);
    cp->primerolibre++;
}
NodoCola eliminar(ColaPrio cp)
{
    assert(cp->primerolibre > 1);
    NodoCola extraido = cp->array[1];

    cp->array[1] = cp->array[cp->primerolibre - 1];
    cp->primerolibre--;

    if (cp->primerolibre > 1)
    {
        hundir(cp, 1);
    }
    return extraido;
}
