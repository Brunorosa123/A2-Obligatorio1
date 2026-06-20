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

string GreedySol(Letra *letras,int N, int maxf){
    
    if((N + 1) / 2 < maxf){
        return "Imposible";
    }

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