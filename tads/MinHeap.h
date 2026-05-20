#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <cassert>

struct NodoHeap;

struct MinHeap;

typedef MinHeap *MinHeapPtr;

/*
PRE: capacidad > 0
POS: Retorna un MinHeap vacío con la capacidad indicada.
*/
MinHeapPtr crearHeap(int capacidad);

/*
PRE: heap != NULL y la cola no está llena
POS: Inserta nodo en el heap manteniendo la propiedad de Min-Heap por dist.
*/
void insertarHeap(NodoHeap nodo, MinHeapPtr heap);

/*
PRE: heap != NULL y el heap no está vacío
POS: Elimina y retorna el nodo con menor dist (la raíz).
*/
NodoHeap extraerMin(MinHeapPtr heap);

/*
PRE: heap != NULL
POS: Retorna true si el heap está vacío.
*/
bool heapVacio(MinHeapPtr heap);

/*
PRE: heap != NULL
POS: Libera la memoria del heap.
*/
void destruirHeap(MinHeapPtr heap);

#endif
