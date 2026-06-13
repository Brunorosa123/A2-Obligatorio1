#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Competidor {
    int pos;
    int tiempototal;
};

bool EsSolucionTrivial(int inicio, int fin) {
    return inicio >= fin;
}

bool EsPrimero(Competidor a, Competidor b) {
    if (a.tiempototal < b.tiempototal) return true;
    if (a.tiempototal > b.tiempototal) return false;

    return a.pos < b.pos;
}

void merge(Competidor* arr, Competidor* aux, int inicio, int mitad, int fin) {
    int i = inicio;    
    int j = mitad + 1;   
    int k = inicio;     

    while (i <= mitad && j <= fin) {
        if (EsPrimero(arr[i], arr[j])) {
            aux[k] = arr[i];
            i++;
        } else {
            aux[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mitad) {
        aux[k] = arr[i];
        i++;
        k++;
    }

    while (j <= fin) {
        aux[k] = arr[j];
        j++;
        k++;
    }

    for (int p = inicio; p <= fin; p++) {
        arr[p] = aux[p];
    }
}

void mergeSort(Competidor *array, Competidor *aux, int inicio, int fin)//nos basamos en las ppts y lo adaptamos a nuestro problema, el algoritmo es el mismo pero con la condicion de ordenamiento que nos piden en el ejercicio, tambien lo que dio en clase el profe
{
    if (EsSolucionTrivial(inicio, fin))
    {
        return;
    }

    int medio = inicio + (fin - inicio) / 2;

    mergeSort(array, aux, inicio, medio);
    mergeSort(array, aux, medio + 1, fin);

    merge(array, aux, inicio, medio, fin);
}

int main()
{ int L;
    cin >> L;

    Competidor* competidores = new Competidor[L];
    Competidor* aux = new Competidor[L];

    int tiempo;

    for (int i = 0; i < L; i++) {
        cin >> tiempo;
        competidores[i].tiempototal = tiempo;
        competidores[i].pos = i + 1;
    }

    for (int i = 0; i < L; i++) {
        cin >> tiempo;
        competidores[i].tiempototal += tiempo;
    }

    for (int i = 0; i < L; i++) {
        cin >> tiempo;
        competidores[i].tiempototal += tiempo;
    }
    mergeSort(competidores, aux, 0, L - 1);

     for (int i = 0; i < L; i++) {
        cout << competidores[i].pos << '\n';
    }
 delete[] competidores;
    delete[] aux;

    return 0;
}