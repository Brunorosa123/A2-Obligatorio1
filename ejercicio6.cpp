#include <iostream>

using namespace std;

struct Punto {
    long long x;
    long long y;
    int id; 
};

long long valorAbsoluto(long long valor) {
    return (valor < 0) ? -valor : valor;
}

bool esMenorOIgualX(Punto p1, Punto p2) {
    return (p1.x < p2.x) || (p1.x == p2.x && p1.y <= p2.y);
}

bool esMenorOIgualY(Punto p1, Punto p2) {
    return (p1.y < p2.y) || (p1.y == p2.y && p1.x <= p2.x);
}

bool distanciaCritica(Punto p1, Punto p2, long long distancia) {
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    return (dx * dx + dy * dy) <= (distancia * distancia);
}

void mergeX(Punto *puntos, Punto *aux, int inicio, int mitad, int fin) {
    int i = inicio;
    int j = mitad + 1;
    int k = inicio;
    while (i <= mitad && j <= fin) {
        if (esMenorOIgualX(puntos[i], puntos[j])) {
            aux[k++] = puntos[i++];
        } else {
            aux[k++] = puntos[j++];
        }
    }
    while (i <= mitad) aux[k++] = puntos[i++];
    while (j <= fin) aux[k++] = puntos[j++];
    for (int p = inicio; p <= fin; p++) puntos[p] = aux[p];
}

void mergeSortX(Punto *arr, Punto *aux, int inicio, int fin) {
    if (inicio < fin) {
        int mitad = inicio + (fin - inicio) / 2;
        mergeSortX(arr, aux, inicio, mitad);
        mergeSortX(arr, aux, mitad + 1, fin);
        mergeX(arr, aux, inicio, mitad, fin);
    }
}

void mergeY(Punto *arr, Punto *aux, int inicio, int mitad, int fin) {
    int i = inicio, j = mitad + 1, k = inicio;
    while (i <= mitad && j <= fin) {
        if (esMenorOIgualY(arr[i], arr[j])) {
            aux[k++] = arr[i++];
        } else {
            aux[k++] = arr[j++];
        }
    }
    while (i <= mitad) aux[k++] = arr[i++];
    while (j <= fin) aux[k++] = arr[j++];
    for (int p = inicio; p <= fin; p++) arr[p] = aux[p];
}

void mergeSortY(Punto *arr, Punto *aux, int inicio, int fin) {
    if (inicio < fin) {
        int mitad = inicio + (fin - inicio) / 2;
        mergeSortY(arr, aux, inicio, mitad);
        mergeSortY(arr, aux, mitad + 1, fin);
        mergeY(arr, aux, inicio, mitad, fin);
    }
}

void dividirPorID(Punto *puntosY, Punto *auxY, int inicio, int mitad, int fin) {
    int izq = inicio;
    int der = mitad + 1;
    for (int p = inicio; p <= fin; p++) {
        if (puntosY[p].id <= mitad) {
            auxY[izq++] = puntosY[p];
        } else {
            auxY[der++] = puntosY[p];
        }
    }
    for (int p = inicio; p <= fin; p++) {
        puntosY[p] = auxY[p];
    }
}

int construirBanda(Punto *puntosY, Punto *banda, int inicio, int fin, long long xMedio, long long D) {
    int tamBanda = 0;
    for (int p = inicio; p <= fin; p++) {
        if (valorAbsoluto(puntosY[p].x - xMedio) <= D) {
            banda[tamBanda++] = puntosY[p];
        }
    }
    return tamBanda;
}

bool analizarBanda(Punto *banda, int tamBanda, long long D) {
    for (int p = 0; p < tamBanda; p++) {
        int q = p + 1;
        while (q < tamBanda && banda[q].y - banda[p].y <= D) {
            if (distanciaCritica(banda[p], banda[q], D)) {
                return true;
            }
            q++;
        }
    }
    return false;
}

bool resolver(const Punto *puntosX, Punto *puntosY, Punto *auxY, Punto *banda, int inicio, int fin, long long distancia) {
    if (inicio >= fin) return false;

    int mitad = inicio + (fin - inicio) / 2;
    long long xMedio = puntosX[mitad].x;

    dividirPorID(puntosY, auxY, inicio, mitad, fin);

    if (resolver(puntosX, puntosY, auxY, banda, inicio, mitad, distancia)){
        return true;
    }
    if (resolver(puntosX, puntosY, auxY, banda, mitad + 1, fin, distancia)){
        return true;
    }

    mergeY(puntosY, auxY, inicio, mitad, fin);

    int tamBanda = construirBanda(puntosY, banda, inicio, fin, xMedio, distancia);

    return analizarBanda(banda, tamBanda, distancia);
}

bool existeParCritico(Punto *puntos, int N, long long D) {
    if (N < 2) return false;

    Punto *auxGlobal = new Punto[N];
    Punto *banda = new Punto[N];

    Punto *puntosX = puntos; 
    mergeSortX(puntosX, auxGlobal, 0, N - 1);
    for (int i = 0; i < N; i++) {
        puntosX[i].id = i;
    }

    Punto *puntosY = new Punto[N];
    for (int i = 0; i < N; i++) {
        puntosY[i] = puntosX[i];
    }
    mergeSortY(puntosY, auxGlobal, 0, N - 1);

    bool resultado = resolver(puntosX, puntosY, auxGlobal, banda, 0, N - 1, D);

    delete[] puntosY;
    delete[] auxGlobal;
    delete[] banda;

    return resultado;
}

int main() {
    int N;
    long long D;
    
    if (cin >> N >> D) {
        Punto *puntos = new Punto[N]; 
        for (int i = 0; i < N; i++) {
            cin >> puntos[i].x >> puntos[i].y;
        }

        if (existeParCritico(puntos, N, D)) {
            cout << "true\n";
        } else {
            cout << "false\n";
        }

        delete[] puntos; 
    }
    
    return 0;
}