#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Letra{
char letra;
int frecuencia;
};

Letra* guardarLetras(string S){
    Letra * letras = new Letra[26];

     for(int i = 0; i < 26; i++){
        letras[i].letra = char('a' + i);
        letras[i].frecuencia = 0;
    }

     for(int i = 0; i < S.length() ; i++){
        char c = S[i];
        int index = c - 'a';
        letras[index].frecuencia++;
    }
    return letras;
}

int FrecuenciaMax(Letra* letras){
    int maxf = 0;
    for(int i = 0; i < 26; i++){
        if(letras[i].frecuencia > maxf){
            maxf = letras[i].frecuencia;
        }
    }
    return maxf;
}

bool sePuedeCompletar(Letra* letras, int restantes, int ultima){
    for(int i = 0; i < 26; i++){
        if(i == ultima){
            if(letras[i].frecuencia > restantes / 2){
                return false;
            }
        } else {
            if(letras[i].frecuencia > (restantes + 1) / 2){
                return false;
            }
        }
    }

    return true;
}

string GreedySol(Letra *letras, int N, int maxf){
    if((N + 1) / 2 < maxf){
        return "Imposible";
    }

    string result = "";
    int ultima = -1;

    for(int pos = 0; pos < N; pos++){
        bool agregado = false;
        for(int i = 25; i >= 0; i--){
            if(letras[i].frecuencia > 0 && i != ultima){
                letras[i].frecuencia--;
                int restantes = N - pos - 1;
                if(sePuedeCompletar(letras, restantes, i)){
                    result += letras[i].letra;
                    ultima = i;
                    agregado = true;
                    break;
                }
                letras[i].frecuencia++;
            }
        }
        if(!agregado){
            return "Imposible";
        }
    }

    return result;
}

int main()
{
    string S;
    cin >> S;
    
    Letra *letras = guardarLetras(S);
    int maxf = FrecuenciaMax(letras);
    int largo = S.length();
    string res = GreedySol(letras, largo, maxf);
    
    cout << res << endl;
   
    delete[] letras;
    return 0;
}