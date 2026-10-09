#include <iostream>
#include <string>
#include "tads/OpenHash.cpp"

using namespace std;

string obtenerClave(string palabra) {
    string clave(26, 'a');
    for (int i = 0; i < (int)palabra.size(); i++) {
        clave[palabra[i] - 'a']++;
    }
    return clave;
}

int main() {
    int n;
    cin >> n;

    HashAbierto * tabla = new HashAbierto(n);
    int mayorCajon = 0;

    for (int i = 0; i < n; i++) {
        string palabra;
        cin >> palabra;
        int cantidad = tabla->sumarUno(obtenerClave(palabra));
        if (cantidad > mayorCajon) {
            mayorCajon = cantidad;
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string palabra;
        cin >> palabra;
        cout << tabla->obtener(obtenerClave(palabra)) << '\n';
    }

    cout << tabla->cantidadElementos() << " " << mayorCajon << '\n';

    delete tabla;
    return 0;
}