#ifndef MFSET_CPP
#define MFSET_CPP

#include <iostream>
using namespace std;

class MFSet {
private:
    int* padre; 
    int* altura;   
    int largo;

public:
    MFSet(int n) {
        this->largo = n + 1;
        this->padre = new int[this->largo];
        this->altura = new int[this->largo];
        for (int i = 0; i < this->largo; i++) {
            this->padre[i] = i;
            this->altura[i] = 0;
        }
    }

    ~MFSet() {
        delete[] this->padre;
        delete[] this->altura;
    }

    int representante(int a) {
        if (a == this->padre[a]) {
            return a;
        }
        this->padre[a] = representante(this->padre[a]);  
        return this->padre[a];
    }

    bool unir(int a, int b) {
        int repA = representante(a);
        int repB = representante(b);
        if (repA == repB) {
            return false;
        }
        if (this->altura[repA] < this->altura[repB]) {
            this->padre[repA] = repB;          
        } else if (this->altura[repA] > this->altura[repB]) {
            this->padre[repB] = repA;
        } else {
            this->padre[repB] = repA;         
            this->altura[repA]++;
        }
        return true;
    }
};

#endif