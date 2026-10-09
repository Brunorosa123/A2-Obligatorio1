#include <iostream>
#include <string>
#include "tads/AvlImp.cpp"

using namespace std;

void imprimirMoneda(const long long& numCat) {
    cout << numCat << "\n";
}

void imprimirPintura(const string& titulo) {
    cout << titulo << "\n";
}

int main() {
    int N;
    cin >> N;

    ArbolAVL<long long> monedas;
    ArbolAVL<string> pinturas;

    for (int i = 0; i < N; ++i) {
        string operacion, coleccion;
        cin >> operacion >> coleccion;

        if (operacion == "ALTA") {
            if (coleccion == "M") {
                long long numCat;
                cin >> numCat;
                monedas.insertar(numCat);
            } else {
                string titulo;
                cin >> titulo;
                pinturas.insertar(titulo);
            }
        } else if (operacion == "BUSCAR") {
            if (coleccion == "M") {
                long long numCat;
                cin >> numCat;
                if (monedas.pertenece(numCat)){
                    cout << "si\n";
                } else {
                    cout << "no\n";
                }
            } else {
                string titulo;
                cin >> titulo;
                if (pinturas.pertenece(titulo)) {
                    cout << "si\n";
                } else {
                    cout << "no\n";
                }
            }
        } else if (operacion == "RANGO"){ 
            if (coleccion == "M") {
                long long desde, hasta;
                cin >> desde >> hasta;
                monedas.rango(desde, hasta, imprimirMoneda);
            } else {
                string desde, hasta;
                cin >> desde >> hasta;
                pinturas.rango(desde, hasta, imprimirPintura);
            }
        }
    }
    return 0;
}