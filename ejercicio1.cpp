#include <string>
#include <iostream>
#include "./tads/HashClosedImp.cpp"

using namespace std;

int main()
{
    int n;
    cin >> n;
    tabla t = crearTabla(n);
    int pedir = 0;
    string datos;
    cin >> datos;
    for (int i = 0; i < datos.length(); i++)
    {
        if (i % 2 == 0)
        {
            insertar(t, datos[i]);  
        }
        else
        {
            char puerta = datos[i] - 'A' + 'a';  
            if (buscar(t, puerta) == 0)
            {
                pedir++;
            }
            else
            {
                eliminar(t, puerta);
            }
        }
    }
    cout << pedir << endl;
    return 0;
}
