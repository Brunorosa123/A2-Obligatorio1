#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Punto
{
    long long x;
    long long y;
};

bool calcularDistancia(Punto *puntos, int i, int f, long long D)
{
    long long dx = puntos[f].x - puntos[i].x;
    long long dy = puntos[f].y - puntos[i].y;

    long long distanciaCuadrada = dx * dx + dy * dy;
    long long dCuadrado = D * D;

    return distanciaCuadrada <= dCuadrado;
}

long long valorAbsoluto(long long valor)
{
    return (valor < 0) ? -valor : valor;
}

bool vaAntesX(Punto a, Punto b)
{
    if (a.x < b.x)
        return true;
    if (a.x > b.x)
        return false;

    return a.y < b.y;
}

bool vaAntesY(Punto a, Punto b)
{
    if (a.y < b.y)
        return true;
    if (a.y > b.y)
        return false;

    return a.x < b.x;
}

void mergeX(Punto *arr, Punto *aux, int inicio, int medio, int fin)
{
    int i = inicio;
    int j = medio + 1;
    int k = inicio;

    while (i <= medio && j <= fin)
    {
        if (vaAntesX(arr[i], arr[j]))
        {
            aux[k] = arr[i];
            i++;
        }
        else
        {
            aux[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= medio)
    {
        aux[k] = arr[i];
        i++;
        k++;
    }

    while (j <= fin)
    {
        aux[k] = arr[j];
        j++;
        k++;
    }

    for (int p = inicio; p <= fin; p++)
    {
        arr[p] = aux[p];
    }
}

void mergeY(Punto *arr, Punto *aux, int inicio, int mitad, int fin)
{
    int i = inicio;
    int j = mitad + 1;
    int k = inicio;

    while (i <= mitad && j <= fin)
    {
        if (vaAntesY(arr[i], arr[j]))
        {
            aux[k] = arr[i];
            i++;
        }
        else
        {
            aux[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mitad)
    {
        aux[k] = arr[i];
        i++;
        k++;
    }

    while (j <= fin)
    {
        aux[k] = arr[j];
        j++;
        k++;
    }

    for (int p = inicio; p <= fin; p++)
    {
        arr[p] = aux[p];
    }
}

void mergeSortY(Punto *arr, Punto *aux, int inicio, int fin)
{
    if (inicio >= fin)
    {
        return;
    }

    int mitad = inicio + (fin - inicio) / 2;

    mergeSortY(arr, aux, inicio, mitad);
    mergeSortY(arr, aux, mitad + 1, fin);

    mergeY(arr, aux, inicio, mitad, fin);
}

void mergeSortX(Punto *arr, Punto *aux, int inicio, int fin)
{
    if (inicio >= fin)
    {
        return;
    }

    int medio = inicio + (fin - inicio) / 2;

    mergeSortX(arr, aux, inicio, medio);
    mergeSortX(arr, aux, medio + 1, fin);

    mergeX(arr, aux, inicio, medio, fin);
}

bool resolver(Punto *puntos, int inicio, int fin, long long D)
{
    int cantidad = fin - inicio + 1;

    if (cantidad < 2)
    {
        return false;
    }

    if (cantidad == 2)
    {
        return calcularDistancia(puntos, inicio, fin, D);
    }

    int medio = inicio + (fin - inicio) / 2;
    long long xMedio = puntos[medio].x;

    // Conquistar izquierda
    if (resolver(puntos, inicio, medio, D))
    {
        return true;
    }

    // Conquistar derecha
    if (resolver(puntos, medio + 1, fin, D))
    {
        return true;
    }

    Punto *banda = new Punto[cantidad];
    int tamBanda = 0;

    for (int i = inicio; i <= fin; i++)
    {
        if (valorAbsoluto(puntos[i].x - xMedio) <= D)
        {
            banda[tamBanda] = puntos[i];
            tamBanda++;
        }
    }

    if (tamBanda >= 2)
    {
        Punto *auxBanda = new Punto[tamBanda];

        mergeSortY(banda, auxBanda, 0, tamBanda - 1);

        for (int i = 0; i < tamBanda; i++)
        {
            int j = i + 1;

            while (j < tamBanda && banda[j].y - banda[i].y <= D)
            {
                if (calcularDistancia(banda, i, j, D))
                {
                    delete[] banda;
                    delete[] auxBanda;
                    return true;
                }

                j++;
            }
        }

        delete[] auxBanda;
    }

    delete[] banda;

    return false;
}

bool existeParCritico(Punto *puntos, int N, long long D)
{
    if (N < 2)
    {
        return false;
    }

    Punto *aux = new Punto[N];

    // Primero ordenamos por X, como indica el pseudocódigo.
    mergeSortX(puntos, aux, 0, N - 1);

    delete[] aux;

    return resolver(puntos, 0, N - 1, D);
}

int main()
{
    int N;
    long long D;

    cin >> N >> D;
    Punto *puntos = new Punto[N];

    for (int i = 0; i < N; i++)
    {
        cin >> puntos[i].x >> puntos[i].y;
    }

    bool respuesta = existeParCritico(puntos, N, D);

    if (respuesta)
    {
        cout << "true" << '\n';
    }
    else
    {
        cout << "false" << '\n';
    }

    delete[] puntos;

    return 0;
}