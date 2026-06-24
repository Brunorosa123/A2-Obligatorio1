#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "./tads/HashClosedStringImp.cpp"



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
        int prev = buscarPuntaje(t, names[i]);
        insertar2(t, names[i], prev + scores[i]);
    }

    int maxScore = getMax(t);

    tabla2 t2 = crearTabla2(n * 2 + 1);
    for (int i = 0; i < n; i++) {
        int prev = buscarPuntaje(t2, names[i]);
        insertar2(t2, names[i], prev + scores[i]);

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
   