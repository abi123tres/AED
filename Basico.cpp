#include <iostream>
using namespace std;

// 1. El nodo de la lista enlazada
/*struct Nodo {
    int clave;
    int valor;
    Nodo* sig;

    Nodo(int c, int v) : clave(c), valor(v), sig(nullptr) {}
};

// 2. La tabla de buckets (iniciada en nullptr)
const int M = 7;
Nodo* tabla[M] = {nullptr};

// 3. Función hash por división
int hash_func(int clave) {
    return ((clave % M) + M) % M; // Maneja enteros positivos y negativos
}

// Inserta una clave con su valor (o actualiza si ya existe)
void insertar(int clave, int valor) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];

    // Paso A: Verificar si la clave ya existe para actualizarla
    while (actual != nullptr) {
        if (actual->clave == clave) {
            actual->valor = valor;
            return;
        }
        actual = actual->sig;
    }

    // Paso B: Si no existe, insertar al frente (push_front)
    Nodo* nuevo = new Nodo(clave, valor);
    nuevo->sig = tabla[idx];
    tabla[idx] = nuevo;
}

// Devuelve el valor asociado a la clave, o -1 si no existe
int buscar(int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];

    while (actual != nullptr) {
        if (actual->clave == clave) {
            return actual->valor; // Encontrado
        }
        actual = actual->sig;
    }

    return -1; // No existe
}

bool contiene(int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == clave) {
            return true;
        }
        actual = actual->sig;
    }
    return false;
}

void eliminar(int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->clave == clave) {
            // Caso 1: Estaba en la cabeza de la lista
            if (anterior == nullptr) {
                tabla[idx] = actual->sig;
            }
            // Caso 2: Estaba en el medio o al final
            else {
                anterior->sig = actual->sig;
            }

            delete actual; // Liberar memoria del nodo
            return;        // Trabajo terminado
        }

        // Si este nodo no era el que buscábamos, ambos dan un paso adelante:
        anterior = actual;
        actual = actual->sig;
    }
}
*/


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
    int valor;
    Nodo* sig;

    Nodo(string c, int v) : clave(c), valor(v), sig(nullptr) {}
};

const int M = 11; // Número primo pequeño para probar
Nodo* tabla[M] = {nullptr};

void contar_palabra(string palabra) {
    int idx = hash_string(palabra, M);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == palabra) {
            actual->valor++;
            return;
        }
        else {
            actual = actual->sig;
        }
    }
    Nodo* nuevo = new Nodo(palabra, 1);
    nuevo->sig = tabla[idx];
    tabla[idx] = nuevo;
}