#include <iostream>

using namespace std;

struct Punto
{
    long long x;
    long long y;
    int id;
};

long long valorAbsoluto(long long valor)
{
    return (valor < 0) ? -valor : valor;
}

bool calcularDistancia(Punto a, Punto b, long long D)
{
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;

    long long distanciaCuadrada = dx * dx + dy * dy;
    long long dCuadrado = D * D;

    return distanciaCuadrada <= dCuadrado;
}

bool vaAntesX(Punto a, Punto b)
{
    if (a.x < b.x)
        return true;
    if (a.x > b.x)
        return false;

    if (a.y < b.y)
        return true;
    if (a.y > b.y)
        return false;

    return a.id < b.id;
}

bool vaAntesY(Punto a, Punto b)
{
    if (a.y < b.y)
        return true;
    if (a.y > b.y)
        return false;

    if (a.x < b.x)
        return true;
    if (a.x > b.x)
        return false;

    return a.id < b.id;
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

void mergeY(Punto *arr, Punto *aux, int inicio, int medio, int fin)
{
    int i = inicio;
    int j = medio + 1;
    int k = inicio;

    while (i <= medio && j <= fin)
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

void mergeSortY(Punto *arr, Punto *aux, int inicio, int fin)
{
    if (inicio >= fin)
    {
        return;
    }

    int medio = inicio + (fin - inicio) / 2;

    mergeSortY(arr, aux, inicio, medio);
    mergeSortY(arr, aux, medio + 1, fin);

    mergeY(arr, aux, inicio, medio, fin);
}

bool resolver(Punto *puntosX, Punto *puntosY, int n, long long D, bool *estaIzq)
{
    if (n < 2)
    {
        return false;
    }

    if (n == 2)
    {
        return calcularDistancia(puntosX[0], puntosX[1], D);
    }

    int medio = (n - 1) / 2;
    int cantIzq = medio + 1;
    int cantDer = n - cantIzq;

    long long xMedio = puntosX[medio].x;

    for (int i = 0; i < cantIzq; i++)
    {
        estaIzq[puntosX[i].id] = true;
    }

    Punto *yIzq = new Punto[cantIzq];
    Punto *yDer = new Punto[cantDer];

    int posIzq = 0;
    int posDer = 0;

    for (int i = 0; i < n; i++)
    {
        if (estaIzq[puntosY[i].id])
        {
            yIzq[posIzq] = puntosY[i];
            posIzq++;
        }
        else
        {
            yDer[posDer] = puntosY[i];
            posDer++;
        }
    }

    for (int i = 0; i < cantIzq; i++)
    {
        estaIzq[puntosX[i].id] = false;
    }

    if (resolver(puntosX, yIzq, cantIzq, D, estaIzq))
    {
        delete[] yIzq;
        delete[] yDer;
        return true;
    }

    if (resolver(puntosX + cantIzq, yDer, cantDer, D, estaIzq))
    {
        delete[] yIzq;
        delete[] yDer;
        return true;
    }

    Punto *banda = new Punto[n];
    int tamBanda = 0;

    // puntosY ya está ordenado por Y, por eso la banda queda ordenada por Y.
    for (int i = 0; i < n; i++)
    {
        if (valorAbsoluto(puntosY[i].x - xMedio) <= D)
        {
            banda[tamBanda] = puntosY[i];
            tamBanda++;
        }
    }

    for (int i = 0; i < tamBanda; i++)
    {
        for (int j = i + 1; j < tamBanda && j <= i + 8; j++)
        {
            if (banda[j].y - banda[i].y > D)
            {
                break;
            }

            if (calcularDistancia(banda[i], banda[j], D))
            {
                delete[] yIzq;
                delete[] yDer;
                delete[] banda;
                return true;
            }
        }
    }

    delete[] yIzq;
    delete[] yDer;
    delete[] banda;

    return false;
}

bool existeParCritico(Punto *puntos, int N, long long D)
{
    if (N < 2)
    {
        return false;
    }

    Punto *puntosX = new Punto[N];
    Punto *puntosY = new Punto[N];

    for (int i = 0; i < N; i++)
    {
        puntosX[i] = puntos[i];
        puntosY[i] = puntos[i];
    }

    Punto *aux = new Punto[N];

    mergeSortX(puntosX, aux, 0, N - 1);
    mergeSortY(puntosY, aux, 0, N - 1);

    delete[] aux;

    bool *estaIzq = new bool[N];

    for (int i = 0; i < N; i++)
    {
        estaIzq[i] = false;
    }

    bool respuesta = resolver(puntosX, puntosY, N, D, estaIzq);

    delete[] puntosX;
    delete[] puntosY;
    delete[] estaIzq;

    return respuesta;
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
        puntos[i].id = i;
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