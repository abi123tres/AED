#include <iostream>
using namespace std;

struct Nodo {
    int clave;
    int valor;
    Nodo* sig;

    Nodo(int c, int v) : clave(c), valor(v), sig(nullptr) {}
};

// 2. La tabla de buckets (iniciada en nullptr)
const int M = 1000003;
Nodo* tabla[M] = {nullptr};

// 3. Función hash por división
int hash_func(int clave) {
    return ((clave % M) + M) % M; // Maneja enteros positivos y negativos
}

void insertar(int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == clave) {
            actual->valor++;
            return;
        }
        actual = actual->sig;
    }
    Nodo* nuevo = new Nodo(clave, 1);
    nuevo->sig = tabla[idx];
    tabla[idx] = nuevo;
}

int contar_frecuencia(int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == clave) {
            return actual->valor;
        }
        actual = actual->sig;
    }
    return 0;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        insertar(a[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (contar_frecuencia(a[i]) == 1) {
            cout << a[i] << "\n";
            return 0;
        }
    }
    cout << -1;
    return 0;
}

