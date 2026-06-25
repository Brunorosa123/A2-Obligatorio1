#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

bool esSolucion(int n) {
    return n == 1;
}

bool esValida(int resultado) {
    return resultado > 0;
}

void aplicarOperacion(int nums[], int &n, int i, int j, int resultado) {
    nums[i] = resultado;
    nums[j] = nums[n - 1];
    n--;
}

void deshacerOperacion(int nums[], int &n, int i, int j, int valorI, int valorJ) {
    n++;
    nums[i] = valorI;
    nums[j] = valorJ;
}

void resolver(int nums[], int n, int objetivo, bool &encontreSolucion) {
    if (encontreSolucion) return;

    if (esSolucion(n)) {
        if (nums[0] == objetivo) {
            encontreSolucion = true;
        }
        return;
    }

    for (int i = 0; i < n && !encontreSolucion; i++) {
        for (int j = 0; j < n && !encontreSolucion; j++) {
            if (i == j) continue;

            int a = nums[i];
            int b = nums[j];

            int resultados[4];
            int cantResultados = 0;

            resultados[cantResultados++] = a + b;

            if (a > b)
                resultados[cantResultados++] = a - b;

            resultados[cantResultados++] = a * b;

            if (b > 0 && a % b == 0)
                resultados[cantResultados++] = a / b;

            for (int r = 0; r < cantResultados && !encontreSolucion; r++) {
                if (esValida(resultados[r])) {
                    aplicarOperacion(nums, n, i, j, resultados[r]);
                    resolver(nums, n, objetivo, encontreSolucion);
                    deshacerOperacion(nums, n, i, j, a, b);
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    int nums[5];
    for (int i = 0; i < n; i++) cin >> nums[i];

    int objetivo;
    cin >> objetivo;

    bool encontreSolucion = false;
    resolver(nums, n, objetivo, encontreSolucion);

    cout << (encontreSolucion ? 1 : 0) << endl;

    return 0;
}