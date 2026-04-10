#include "HashClosedString.h"
#include <cctype>
#include <string>
#include <climits>


struct NodoStr{
    std::string clave;
    bool ocupado;
    int puntaje;
};

struct TablaStr{
    NodoStr* array;
    int tam;
};

typedef TablaStr* tabla2;

int hash1(std::string key, int tam) {
    int h = 0;
    for (int i = 0; i < key.length(); i++)
        h = (h * 31 + key[i]) % tam;
    return h;
}

int hash2(std::string key, int tam) {
     int h = 0; 
     for (int i = 0; i < key.length(); i++) 
        h = (h * 37 + key[i]) % tam; 
    return (h % (tam - 1)) + 1; 
}

tabla2 crearTabla2(int tam) {
    tabla2 t = new TablaStr;
    t->tam = tam;
    t->array = new NodoStr[tam];

    for (int i = 0; i < tam; i++) {
        t->array[i].ocupado = false;
        t->array[i].puntaje = 0;
    }
    return t;
}

void insertar2(tabla2 t, std::string key, int score) {
    int h1 = hash1(key, t->tam);
    int h2 = hash2(key, t->tam);

    for (int i = 0; i < t->tam; i++) {
        int index = (h1 + i * h2) % t->tam;

        if (!t->array[index].ocupado) {
            t->array[index].clave = key;
            t->array[index].puntaje = score;
            t->array[index].ocupado = true;
            return;
        }

        if (t->array[index].clave == key) {
            t->array[index].puntaje += score;
            return;
        }
    }
}

int buscarPuntaje(tabla2 t, std::string key) {
    int h1 = hash1(key, t->tam);
    int h2 = hash2(key, t->tam);

    for (int i = 0; i < t->tam; i++) {
        int pos = (h1 + i * h2) % t->tam;

        if (t->array[pos].ocupado && t->array[pos].clave == key) {
            return t->array[pos].puntaje;
        }
    }
    return 0;
}

int getMax(tabla2 t) {
    int max = INT_MIN;
    for (int i = 0; i < t->tam; i++) {
        if (t->array[i].ocupado && t->array[i].puntaje > max)
            max = t->array[i].puntaje;
    }
    return max;
}
