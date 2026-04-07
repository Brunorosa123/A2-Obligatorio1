#include "HashClosed.h"
#include <cctype>
#include <string>

struct Nodo {
    char clave;
    int cantidad;
    bool ocupado;
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

