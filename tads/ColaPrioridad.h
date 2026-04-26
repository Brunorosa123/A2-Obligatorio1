#ifndef COLA_PRIORIDAD_H
#define COLA_PRIORIDAD_H

#include <cassert>
/*
PRE: capacidad > 0
POS: Retorna una Cola de Prioridad vacía, inicializada con la capacidad indicada
     y el primer lugar libre en la posición 1.
*/
ColaPrio crearCola(int capacidad);

/*
PRE: cp != NULL y la cola no está llena (cp->primerolibre <= cp->capacidad)
POS: Inserta el paciente (nodo) en la cola manteniendo la estructura de 
     Max-Heap según urgencia, hora de llegada y orden de ingreso.
*/
void insertar(NodoCola nodo, ColaPrio cp);

/*
PRE: cp != NULL y la cola no está vacía (cp->primerolibre > 1)
POS: Elimina de la estructura y retorna el paciente con mayor prioridad 
     (la raíz del Max-Heap), reacomodando los elementos restantes.
*/
NodoCola eliminar(ColaPrio cp);


// --- Funciones Auxiliares y Matemáticas ---

/*
PRE: pos > 1
POS: Retorna el índice correspondiente al padre del nodo en la posición 'pos'.
*/
int padre(int pos);

/*
PRE: pos >= 1
POS: Retorna el índice correspondiente al hijo izquierdo del nodo en la posición 'pos'.
*/
int hijoizq(int pos);

/*
PRE: pos >= 1
POS: Retorna el índice correspondiente al hijo derecho del nodo en la posición 'pos'.
*/
int hijoder(int pos);

/*
PRE: Ambas estructuras NodoCola están correctamente inicializadas.
POS: Retorna true si n1 tiene estrictamente mayor prioridad que n2 basándose en:
     1. Mayor urgencia.
     2. Menor hora (en caso de empate).
     3. Menor orden de llegada (en caso de empate).
*/
bool mayorPrioridad(NodoCola n1, NodoCola n2);

/*
PRE: cp != NULL. 'a' y 'b' son índices válidos dentro del arreglo (1 <= a,b < cp->primerolibre).
POS: Intercambia de lugar los elementos ubicados en las posiciones 'a' y 'b'.
*/
void intercambiar(ColaPrio cp, int a, int b);

/*
PRE: cp != NULL. 'pos' es un índice válido (1 <= pos < cp->primerolibre).
POS: Compara el elemento en 'pos' con su padre y lo hace subir (flotar) por el árbol 
     hasta que se cumpla la propiedad de Max-Heap.
*/
void flotar(ColaPrio cp, int pos);

/*
PRE: cp != NULL. 'pos' es un índice válido (1 <= pos < cp->primerolibre).
POS: Compara el elemento en 'pos' con sus hijos y lo hace bajar (hundir) por el árbol 
     hasta que se cumpla la propiedad de Max-Heap.
*/
void hundir(ColaPrio cp, int pos);

#endif 