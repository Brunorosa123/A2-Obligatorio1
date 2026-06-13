#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "./tads/ColaPrioridadImp.cpp"

using namespace std;

int main()
{
    int n;
    cin >> n;

    int *idPaciente = new int[n + 1];
    int *hora = new int[n + 1];
    int *Urgencia = new int[n + 1];

    for (int i = 1; i <= n; i++)
    {
        cin >> idPaciente[i] >> hora[i] >> Urgencia[i];
    }

    ColaPrio cp = crearCola(n);
    for (int i = 1; i <= n; i++)
    {

        NodoCola nodo;
        nodo.Pac = idPaciente[i];
        nodo.Hora = hora[i];
        nodo.Urg = Urgencia[i];
        nodo.orden = i;

        insertar(nodo, cp);
    }
    for (int i = 1; i <= n; i++)
    {
        NodoCola nodo = eliminar(cp);
        cout << nodo.Pac << "\n";
    }

    delete[] idPaciente;
    delete[] hora;
    delete[] Urgencia;

    return 0;
}