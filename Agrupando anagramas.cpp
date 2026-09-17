#include <iostream>
using namespace std;

int hash_string(string clave, int M) {
    long long h = 0;
    long long B = 131; // Base prima mayor que los caracteres ASCII comunes

    for (char c : clave) {
        h = (h * B + c) % M;
    }

    return h;
}

struct Nodo {
    string clave;
    Nodo* sig;

    Nodo(string c) : clave(c), sig(nullptr) {}
};

const int M = 1000003; // Número primo pequeño para probar
Nodo* tabla[M] = {nullptr};

bool insertarNoRepetido(string clave) {
    int idx = hash_string(clave, M);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == clave) {
            return false;
        }
        actual = actual->sig;
    }
    Nodo* nuevo = new Nodo(clave);
    nuevo->sig = tabla[idx];
    tabla[idx] = nuevo;
    return true;
}