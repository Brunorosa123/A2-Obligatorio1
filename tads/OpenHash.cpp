#include <iostream>
#include <string>
using namespace std;

// Basado en clase-02-hash-cerrado-main: esPrimo, primoSup, constructor con
// "esperados", función de hash, cantidadElementos y destructor.
// Adaptado a hash abierto con una lista enlazada por posición.
class HashAbierto {
    private:
        class NodoHash {
            public:
                string clave;
                int cantidad;
                NodoHash * sig;
                NodoHash(string clave) : clave(clave), cantidad(0), sig(NULL) {}
        };

        NodoHash ** tabla;  
        int largoTabla;     
        int cantElementos;

        bool esPrimo(int num) {
            if (num < 2) return false;
            for (int i = 2; i * i <= num; i++) {
                if (num % i == 0) return false;
            }
            return true;
        }

        int primoSup(int num) {
            while (!esPrimo(++num));
            return num;
        }

        int funcionHash(string clave) {
            int hash = 0;
            for (int i = 0; i < (int)clave.size(); i++) {
                hash = (hash * 131 + (unsigned char)clave[i]) % this->largoTabla;
            }
            return hash;
        }

        NodoHash * buscarEnBucket(int posicion, string clave) {
            NodoHash * actual = this->tabla[posicion];
            while (actual != NULL && actual->clave != clave) {
                actual = actual->sig;
            }
            return actual;
        }

    public:
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

        int sumarUno(string clave) {
            int posicion = this->funcionHash(clave);
            NodoHash * nodo = this->buscarEnBucket(posicion, clave);
            if (nodo == NULL) {
                nodo = new NodoHash(clave);
                nodo->sig = this->tabla[posicion]; 
                this->tabla[posicion] = nodo;
                this->cantElementos++;
            }
            nodo->cantidad++;
            return nodo->cantidad;
        }

        int obtener(string clave) {
            NodoHash * nodo = this->buscarEnBucket(this->funcionHash(clave), clave);
            if (nodo == NULL) {
                return 0;
            }
            return nodo->cantidad;
        }

        int cantidadElementos() {
            return this->cantElementos;
        }
};