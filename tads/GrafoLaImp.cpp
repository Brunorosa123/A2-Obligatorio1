#include <climits>
#include <iostream>

struct NodoGrafo
{
    int vertice;
    int peso;
    NodoGrafo *sig;

    NodoGrafo(int v, int p, NodoGrafo *s = NULL)
    {
        vertice = v;
        peso = p;
        sig = s;
    }
};

typedef NodoGrafo *ListaAdyLA;

class GrafoLA
{
private:
    int numVertices;
    int numAristas;
    ListaAdyLA *vec;
    bool dirigido;
    bool ponderado;

public:
    GrafoLA(int vertices, int aristas, bool dirigido = false, bool ponderado = false)
    {
        this->numVertices = vertices;
        this->dirigido = dirigido;
        this->ponderado = ponderado;
        this->numAristas = aristas;
        this->vec = new ListaAdyLA[vertices + 1]();
    }

    int obtenerVertices()
    {
        return this->numVertices;
    }

    int obtenerAristas()
    {
        return this->numAristas;
    }

    NodoGrafo *obtenerAdyacentes(int v)
    {
        return this->vec[v];
    }

    void RellenarVec(int* costos, int* vengoDe, bool* visitados, int n) 
    {

        for (int i = 1; i <= n; i++)
        {
            costos[i] = INT_MAX;
            vengoDe[i] = -1;
            visitados[i] = false;
        }
       return;
    }

       void insertarArista(int o, int d, int peso = 1){
        if(!ponderado) peso = 1;

        NodoGrafo* nodo = new NodoGrafo(d, peso, this->vec[o]);
        this->vec[o] = nodo;

        if(!this->dirigido){
            NodoGrafo* inversa = new NodoGrafo(o, peso, this->vec[d]);
            this->vec[d] = inversa;
        }
    }
};
