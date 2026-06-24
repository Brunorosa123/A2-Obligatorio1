#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;


struct Objeto {
    int peso;
    int volumen;
    int costo;
    int valor;
    bool supervivencia;
};

struct Estado {
    int valor;
    int peso;
    int cantidad;
};

bool mejorEstado(Estado a, Estado b) {
    if (a.valor != b.valor) return a.valor > b.valor;
    if (a.peso != b.peso) return a.peso < b.peso;
    return a.cantidad < b.cantidad;
}

int calcularIndice(int p, int v, int c, int s, int m, int dimV, int dimC, int dimSup, int dimCom) {
    return (((p * dimV + v) * dimC + c) * dimSup + s) * dimCom + m;
}

int main() {
    int n;
    cin >> n;

    int P, V, C, S, M;
    cin >> P >> V >> C >> S >> M;

    Objeto* objetos = new Objeto[n];

    for (int i = 0; i < n; i++) {
        string categoria;

        cin >> objetos[i].peso
            >> objetos[i].volumen
            >> objetos[i].costo
            >> objetos[i].valor
            >> categoria;

        objetos[i].supervivencia = (categoria == "supervivencia");
    }

    int dimP = P + 1;
    int dimV = V + 1;
    int dimC = C + 1;
    int dimSup = S + 1;
    int dimCom = M + 1;

    int totalEstados = dimP * dimV * dimC * dimSup * dimCom;

    Estado* dp = new Estado[totalEstados];

    for (int i = 0; i < totalEstados; i++) {
        dp[i].valor = -1;     
        dp[i].peso = 0;
        dp[i].cantidad = 0;
    }

    int posInicial = calcularIndice(0, 0, 0, 0, 0, dimV, dimC, dimSup, dimCom);
    dp[posInicial].valor = 0;
    dp[posInicial].peso = 0;
    dp[posInicial].cantidad = 0;

    for (int i = 0; i < n; i++) {
        Objeto obj = objetos[i];

        int Sup = 0;
        int Com = 0;

        if (obj.supervivencia) {
            Sup = 1;
        } else {
            Com = 1;
        }

        for (int p = P - obj.peso; p >= 0; p--) {
            for (int v = V - obj.volumen; v >= 0; v--) {
                for (int c = C - obj.costo; c >= 0; c--) {
                    for (int s = S - Sup; s >= 0; s--) {
                        for (int m = M - Com; m >= 0; m--) {

                            int posActual = calcularIndice(p, v, c, s, m, dimV, dimC, dimSup, dimCom);

                            if (dp[posActual].valor == -1) {
                                continue;
                            }

                            int nuevoP = p + obj.peso;
                            int nuevoV = v + obj.volumen;
                            int nuevoC = c + obj.costo;
                            int nuevoS = s + Sup;
                            int nuevoM = m + Com;

                            int posNuevo = calcularIndice(nuevoP, nuevoV, nuevoC,nuevoS, nuevoM, dimV, dimC, dimSup, dimCom);

                            Estado candidato;
                            candidato.valor = dp[posActual].valor + obj.valor;
                            candidato.peso = dp[posActual].peso + obj.peso;
                            candidato.cantidad = dp[posActual].cantidad + 1;

                            if (dp[posNuevo].valor == -1 || mejorEstado(candidato, dp[posNuevo])) {
                                dp[posNuevo] = candidato;

                                
                            }
                        }
                    }
                }
            }
        }
    }

    Estado respuesta;
    respuesta.valor = 0;
    respuesta.peso = 0;
    respuesta.cantidad = 0;

    for (int p = 0; p <= P; p++) {
        for (int v = 0; v <= V; v++) {
            for (int c = 0; c <= C; c++) {
                for (int s = 0; s <= S; s++) {
                    for (int m = 0; m <= M; m++) {

                        int pos = calcularIndice(p, v, c, s, m, dimV, dimC, dimSup, dimCom);

                        Estado actual = dp[pos];

                        if (actual.valor != -1 && mejorEstado(actual, respuesta)) {
                            respuesta = actual;
                        }
                    }
                }
            }
        }
    }

    cout << respuesta.valor << " "
         << respuesta.peso << " "
         << respuesta.cantidad << endl;

    delete[] dp;
    delete[] objetos;

    return 0;
}