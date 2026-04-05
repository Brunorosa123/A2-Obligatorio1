#include <cassert>
#include <string>
#include <iostream>
#include <limits>


using namespace std;

int main()
{
    int n;
    cin >> n;
    tabla t = crearTabla2(n);
    int max = 0; 
    for (int i = 0; i < n; i++)
    {
        string name;
        int score;
        cin >> name >> score;
        insertar2 (t, name, score, 0);
    }
    for (int i = 0; i < n; i++)
    {        
        
        if (buscar2 (t, name) > max)
        {
            max = buscar (t, name);
        }
    }
    int n;
    cin >> n;
    tabla t2 = crearTabla2(n);
    int min = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        string name;
        int score;
        
        insertar2 (t2, names[i], scores[i], 0);
        if (buscar2 (t2, name) == max){
            insertar2 (t2, name, score, i);
        }
    }
    for (int i = 0; i < n; i++)
    {        
        string nameRes;
        if (buscar2 (t2, name) == max)
        {
            if (buscarRonda (t2, name) < min)
            {
                min = buscarRonda (t2, name);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {        
        
        if (buscarRonda (t, name) == min)
        {
            nameRes = name;
        }
    }
    cout << nameRes << endl;

    return 0;
}

/* 
#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int n;
    cin >> n;

    // Guardar entrada en memoria
    string* names = new string[n];
    int* scores = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> names[i] >> scores[i];
    }

    // Primera pasada: calcular puntajes finales
    tabla t = crearTabla2(n);
    for (int i = 0; i < n; i++)
    {
        insertar2(t, names[i], scores[i]);  // acumula el score
    }

    // Encontrar el máximo
    int maxScore = getMax(t);  // función del TAD que recorre internamente

    // Segunda pasada: encontrar primera ronda en que cada candidato alcanzó el máximo
    tabla t2 = crearTabla2(n);
    for (int i = 0; i < n; i++)
    {
        insertar2(t2, names[i], scores[i]);

        if (buscarPuntaje(t, names[i]) == maxScore)
        {
            if (buscarPuntaje(t2, names[i]) == maxScore && buscarRonda(t2, names[i]) == -1)
            {
                setRonda(t2, names[i], i);
            }
        }
    }

    // Encontrar ganador
    string ganador = getGanador(t, t2, maxScore);  // función del TAD que recorre internamente

    cout << ganador << endl;

    delete[] names;
    delete[] scores;

    return 0;
}


*/