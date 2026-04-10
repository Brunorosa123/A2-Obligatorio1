#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "./tads/HashClosedString.cpp"



using namespace std;

int main()
{
    int n;
    cin >> n;
    
    string* names = new string[n];
    int* scores = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> names[i] >> scores[i];
    }

    tabla2 t = crearTabla2(n * 2 + 1);

    for (int i = 0; i < n; i++) {
        insertar2(t, names[i], scores[i]);
    }

    int maxScore = getMax(t);


    tabla2 t2 = crearTabla2(n * 2 + 1);

    for (int i = 0; i < n; i++) {
        insertar2(t2, names[i], scores[i]);

        if (buscarPuntaje(t, names[i]) == maxScore &&
            buscarPuntaje(t2, names[i]) >= maxScore) {
            
            cout << names[i] << endl;
            break;
        }
    }

    delete[] names;
    delete[] scores;

    return 0;
}
   