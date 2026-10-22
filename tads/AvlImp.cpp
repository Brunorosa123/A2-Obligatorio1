#ifndef AVL_CPP
#define AVL_CPP

template <class T>
struct NodoAVL {
    T dato;
    int altura;
    NodoAVL* izq;
    NodoAVL* der;

    NodoAVL(T valor) {
        dato = valor;
        altura = 1;
        izq = NULL;
        der = NULL;
    }
};
// Basado en 01_avl_insercion.cpp de la clase de AVL (clase-01-avl-main):
// inserción recursiva, rotaciones y campo altura.
template <class T>
class ArbolAVL {
    private:
        NodoAVL<T>* raiz;

        int max(int a, int b){ 
            return (a > b) ? a : b; }

        int obtenerAltura(NodoAVL<T>* nodo) {
            if (nodo == NULL) return 0;
            return nodo->altura;
        }

        void actualizarAltura(NodoAVL<T>* nodo) {
            nodo->altura = 1 + max(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));
        }

        int calcBalance(NodoAVL<T>* t) {
            return obtenerAltura(t->der) - obtenerAltura(t->izq);
        }

        NodoAVL<T>* rotacionIzq(NodoAVL<T>* A, NodoAVL<T>* B) {
            A->der = B->izq;
            B->izq = A;
            actualizarAltura(A); 
            actualizarAltura(B);
            return B;
        }

        NodoAVL<T>* rotacionDer(NodoAVL<T>* A, NodoAVL<T>* B) {
            A->izq = B->der;
            B->der = A;
            actualizarAltura(A);
            actualizarAltura(B);
            return B;
        }

        NodoAVL<T>* insertar(NodoAVL<T>* nodo, T valor) {
            if (nodo == NULL) return new NodoAVL<T>(valor);

            if (valor < nodo->dato) {
                nodo->izq = insertar(nodo->izq, valor);
            } else if (nodo->dato < valor) {
                nodo->der = insertar(nodo->der, valor);
            } else {
                return nodo; 
            }

            actualizarAltura(nodo);
            int balance = calcBalance(nodo);

            if (balance < -1 && valor < nodo->izq->dato)
                return rotacionDer(nodo, nodo->izq);
            if (balance > 1 && nodo->der->dato < valor)
                return rotacionIzq(nodo, nodo->der);
            if (balance < -1 && nodo->izq->dato < valor) {
                nodo->izq = rotacionIzq(nodo->izq, nodo->izq->der);
                return rotacionDer(nodo, nodo->izq);
            }
            if (balance > 1 && valor < nodo->der->dato) {
                nodo->der = rotacionDer(nodo->der, nodo->der->izq);
                return rotacionIzq(nodo, nodo->der);
            }
            return nodo;
        }
         // El parámetro 'visitar' (puntero a función) para no imprimir adentro del
        // TAD fue sugerido por IA. La poda del recorrido es propia.
        void rango(NodoAVL<T>* nodo, T desde, T hasta,
                   void (*visitar)(const T&)) {
            if (nodo == NULL) return;

            if (desde < nodo->dato) {
                rango(nodo->izq, desde, hasta, visitar);
            }
            if (!(nodo->dato < desde) && !(hasta < nodo->dato)) {
                visitar(nodo->dato);
            }
            if (nodo->dato < hasta) {
                rango(nodo->der, desde, hasta, visitar);
            }
        }

        void destruirArbol(NodoAVL<T>* nodo) {
            if (nodo != NULL) {
                destruirArbol(nodo->izq);
                destruirArbol(nodo->der);
                delete nodo;
            }
        }

    public:
        ArbolAVL() : raiz(NULL) {}
        ~ArbolAVL() { destruirArbol(raiz); }

        void insertar(T valor) {
            raiz = insertar(raiz, valor);
        }

        bool pertenece(T valor) {
            NodoAVL<T>* t = raiz;
            while (t != NULL) {
                if (valor < t->dato) {
                    t = t->izq;
                } else if (t->dato < valor) {
                    t = t->der;
                } else {
                    return true;
                }
            }
            return false;
        }

        void rango(T desde, T hasta, void (*visitar)(const T&)) {
            rango(raiz, desde, hasta, visitar);
        }
};

#endif