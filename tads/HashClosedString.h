#ifndef HASH_CLOSED_STRING_H
#define HASH_CLOSED_STRING_H

#include <string>

// forward declarations
struct NodoStr;
struct TablaStr;

typedef TablaStr* tabla2;

/*
PRE: tam > 0
POS: Retorna una tabla vacía de tamaño tam
*/
tabla2 crearTabla2(int tam);

/*
PRE: t != NULL
POS: Inserta o acumula puntaje
*/
void insertar2(tabla2 t, std::string key, int score);

/*
PRE: t != NULL
POS: Retorna puntaje de key o 0 si no existe
*/
int buscarPuntaje(tabla2 t, std::string key);

/*
PRE: t != NULL
POS: Retorna el máximo puntaje de la tabla
*/
int getMax(tabla2 t);

#endif