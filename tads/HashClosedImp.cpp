#include "HashClosed.h"
#include <cctype>
#include <string>

struct Nodo {
    char clave;
    int cantidad;
    bool ocupado;
};

struct Nodo2 {
    char clave;
    int cantidad;
    int ronda;
};

struct Tabla{
    Nodo* array;
    int tam;
};

typedef Tabla* tabla;


int hashFunction(char key, int tam) {
    return (std::tolower(key) - 'a') % tam;
}


tabla crearTabla(int tam){
    tabla t = new Tabla ;
    t->tam = tam;
    t->array = new Nodo[tam];
    for (int i = 0; i < tam; i++) {
        t->array[i].ocupado = false;
        t->array[i].cantidad = 0;
    }
    return t;
}


void insertar(tabla t, char key){
    int pos = hashFunction(key, t->tam);
    
    for(int i=0;i<t->tam;i++){
        int index = (pos + i) % t->tam;

        if(!t->array[index].ocupado){
            t->array[index].cantidad = 1;
            t->array[index].clave = key;
            t->array[index].ocupado = true;
            return;
        }
            if(t->array[index].clave == key)
            {
                t->array[index].cantidad++;
                return;
        }
    }
        

    }

int buscar(tabla t, char key){
   int pos = hashFunction(key, t->tam);

    for(int i=0 ; i<t->tam ; i++){
            int index = (pos + i) % t->tam;

        if(!t->array[index].ocupado){
        return 0;
        }
        if(t->array[index].clave == key){
        return t->array[index].cantidad;

        }
    }
       return 0;
}

void eliminar(tabla t, char key){
    int pos = hashFunction(key, t->tam);

    for(int i=0 ; i<t->tam ; i++){
        int index = (pos + i) % t->tam;

        if(!t->array[index].ocupado){
            return;
        }

        if(t->array[index].clave == key){
            t->array[index].cantidad--;

            if(t->array[index].cantidad == 0){
                t->array[index].ocupado = false;
            }
            return;
        }
    }
}


struct Nodo2 {
    string clave;
    int puntaje;
    int primera_ronda;
    bool ocupado;
};

struct Tabla2 {
    Nodo2* array;
    int tam;
};

typedef Tabla2* tabla2;



int hashFunction2(string key, int tam) {
    int h = 0;
    for (char c : key) h = (h * 31 + c) % tam;
    return h;
}

int hashFunction2b(string key, int tam) {
    int h = 0;
    for (char c : key) h = (h * 37 + c) % tam;
    return (h % (tam - 1)) + 1;  // doble hashing, nunca da 0
}

// --- Crear tabla ---

tabla2 crearTabla2(int tam) {
    tabla2 t = new Tabla2;
    t->tam = tam;
    t->array = new Nodo2[tam];
    for (int i = 0; i < tam; i++) {
        t->array[i].ocupado = false;
        t->array[i].puntaje = 0;
        t->array[i].primera_ronda = -1;
    }
    return t;
}

// --- Insertar / acumular puntaje ---

void insertar2(tabla2 t, string key, int score) {
    int h1 = hashFunction2(key, t->tam);
    int h2 = hashFunction2b(key, t->tam);

    for (int i = 0; i < t->tam; i++) {
        int index = (h1 + i * h2) % t->tam;

        if (!t->array[index].ocupado) {
            t->array[index].clave = key;
            t->array[index].puntaje = score;
            t->array[index].primera_ronda = -1;
            t->array[index].ocupado = true;
            return;
        }
        if (t->array[index].clave == key) {
            t->array[index].puntaje += score;  // acumula
            return;
        }
    }
}

// --- Buscar puntaje ---

int buscarPuntaje(tabla2 t, string key) {
    int h1 = hashFunction2(key, t->tam);
    int h2 = hashFunction2b(key, t->tam);

    for (int i = 0; i < t->tam; i++) {
        int index = (h1 + i * h2) % t->tam;

        if (!t->array[index].ocupado) return 0;
        if (t->array[index].clave == key) return t->array[index].puntaje;
    }
    return 0;
}

int buscarRonda(tabla2 t, string key) {
    int h1 = hashFunction2(key, t->tam);
    int h2 = hashFunction2b(key, t->tam);

    for (int i = 0; i < t->tam; i++) {
        int index = (h1 + i * h2) % t->tam;

        if (!t->array[index].ocupado) return -1;
        if (t->array[index].clave == key) return t->array[index].primera_ronda;
    }
    return -1;
}



void setRonda(tabla2 t, string key, int ronda) {
    int h1 = hashFunction2(key, t->tam);
    int h2 = hashFunction2b(key, t->tam);

    for (int i = 0; i < t->tam; i++) {
        int index = (h1 + i * h2) % t->tam;

        if (!t->array[index].ocupado) return;
        if (t->array[index].clave == key) {
            if (t->array[index].primera_ronda == -1) {
                t->array[index].primera_ronda = ronda;
            return;
        }
    }
}

int getMax(tabla2 t) {
    int max = 0;
    for (int i = 0; i < t->tam; i++) {
        if (t->array[i].ocupado && t->array[i].puntaje > max)
            max = t->array[i].puntaje;
    }
    return max;
}


string getGanador(tabla2 t1, tabla2 t2, int maxScore) {
    int minRonda = INT_MAX;
    string ganador = "";

    for (int i = 0; i < t2->tam; i++) {
        if (t2->array[i].ocupado) {
            string nombre = t2->array[i].clave;
            if (buscarPuntaje(t1, nombre) == maxScore) {
                int ronda = buscarRonda(t2, nombre);
                if (ronda < minRonda) {
                    minRonda = ronda;
                    ganador = nombre;
                }
            }
        }
    }
    return ganador;
}