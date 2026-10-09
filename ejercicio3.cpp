#include <iostream>
#include "tads/MinHeap.cpp"
using namespace std;


// Tiempo: N inserciones + (N-1) iteraciones con 2 eliminaciones y 1 inserción,
// todas O(log N) => O(N log N). Espacio: O(N) (el heap nunca supera N elementos).
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    MinHeap* heap = new MinHeap(n);

    for (int i = 1; i <= n; i++) {
        long long cantidad;
        cin >> cantidad;
        heap->insertar(cantidad);
    }

    long long costoTotal = 0;

    while (heap->tamaño() > 1) {
        long long a = heap->eliminarMinimo();
        long long b = heap->eliminarMinimo();
        long long nuevo = a + b;

        costoTotal += nuevo;
        heap->insertar(nuevo);
    }

    cout << costoTotal << endl;
delete heap;

    return 0;
}