#include <iostream>
#include <string>
using namespace std;

// TAD HashAbierto: tabla de hash abierta con resolucion de colisiones por
// ENCADENAMIENTO. Asocia una clave (string) con un contador entero.
//
// Fuentes / adaptado de:
// - Estructura de la clase (clase privada anidada, arreglo de punteros
//   inicializado en NULL, this-> explicito): hashcerrado1.cpp (clase HashCerrado).
// - esPrimo, primoSup, funcionHash con % largo, constructor con "esperados"
//   y destructor: hashcerrado2.cpp (clase Hash).
// - Hash abierto = un bucket con una lista donde se guardan los datos,
//   factor de carga (lambda = N/B) y rango sano 0.5~0.7:
//   03__Tablas_de_Hash_1.pdf (diapositivas 13, 15 y 20).
// - Cambios propios: los buckets son listas enlazadas (en el curso el
//   ejemplo es de hash cerrado) y la funcion de hash recorre TODA la clave.


class HashAbierto {
    private:
        class NodoHash {
            public:
                string clave;
                int cantidad;
                NodoHash * sig;
                NodoHash(string clave) : clave(clave), cantidad(0), sig(NULL) {}
        };

        NodoHash ** tabla;   // cada posicion (bucket) es el inicio de una lista
        int largoTabla;      // cantidad de buckets (primo)
        int cantElementos;   // cantidad de claves distintas guardadas

        // Tomado de hashcerrado2.cpp
        bool esPrimo(int num) {
            if (num < 2) return false;
            for (int i = 2; i * i <= num; i++) {
                if (num % i == 0) return false;
            }
            return true;
        }

        // Tomado de hashcerrado2.cpp
        int primoSup(int num) {
            while (!esPrimo(++num));
            return num;
        }

        // Adaptado de hashcerrado2.cpp. OJO: aca NO se corta en 10 caracteres
        // como en el curso. La clave de este ejercicio tiene 26 caracteres y
        // TODOS distinguen un cajon de otro: si se miraran solo los primeros
        // 10, dos cajones que difieran en las letras k..z colisionarian siempre.
        // Como el largo de la clave es constante (26), sigue siendo O(1).
        int funcionHash(string clave) {
            int hash = 0;
            for (int i = 0; i < (int)clave.size(); i++) {
                hash = (hash * 131 + (unsigned char)clave[i]) % this->largoTabla;
            }
            return hash;
        }

        // Recorre la lista del bucket. Devuelve el nodo o NULL si no esta.
        NodoHash * buscarEnBucket(int posicion, string clave) {
            NodoHash * actual = this->tabla[posicion];
            while (actual != NULL && actual->clave != clave) {
                actual = actual->sig;
            }
            return actual;
        }

    public:
        // "esperados" = cantidad maxima de claves distintas que se van a guardar.
        // Buckets = primo >= 1.5 * esperados  ->  lambda maximo ~ 0.67
        // (dentro del rango sano 0.5~0.7). Como las claves distintas nunca
        // superan a "esperados", el lambda no se pasa de ahi y no hace falta rehash.
        HashAbierto(int esperados) {
            this->largoTabla = primoSup(esperados * 3 / 2);
            this->tabla = new NodoHash*[this->largoTabla];
            for (int i = 0; i < this->largoTabla; i++) {
                this->tabla[i] = NULL;
            }
            this->cantElementos = 0;
        }

        ~HashAbierto() {
            for (int i = 0; i < this->largoTabla; i++) {
                NodoHash * actual = this->tabla[i];
                while (actual != NULL) {
                    NodoHash * borrar = actual;
                    actual = actual->sig;
                    delete borrar;
                }
            }
            delete[] this->tabla;
        }

        // Suma 1 al contador de la clave (la crea si no existe) y devuelve
        // el valor nuevo del contador. O(1) promedio.
        int sumarUno(string clave) {
            int posicion = this->funcionHash(clave);
            NodoHash * nodo = this->buscarEnBucket(posicion, clave);
            if (nodo == NULL) {
                nodo = new NodoHash(clave);
                nodo->sig = this->tabla[posicion]; // se agrega al inicio del bucket: O(1)
                this->tabla[posicion] = nodo;
                this->cantElementos++;
            }
            nodo->cantidad++;
            return nodo->cantidad;
        }

        // Devuelve el contador de la clave, o 0 si la clave no esta.
        // NO inserta nada (consultar no registra). O(1) promedio.
        int obtener(string clave) {
            NodoHash * nodo = this->buscarEnBucket(this->funcionHash(clave), clave);
            if (nodo == NULL) {
                return 0;
            }
            return nodo->cantidad;
        }

        // Cantidad de claves distintas. O(1).
        int cantidadElementos() {
            return this->cantElementos;
        }
};