#include <iostream>
using namespace std;

struct Nodo {
    long long clave;
    Nodo* sig;

    Nodo(long long c) : clave(c), sig(nullptr) {}
};

// 2. La tabla de buckets (iniciada en nullptr)
const int M = 1000003;
Nodo* tabla[M] = {nullptr};

// 3. Función hash por división
int hash_func(int clave) {
    return ((clave % M) + M) % M; // Maneja enteros positivos y negativos
}

void insertar(long long clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];
    // Paso A: Verificar si la clave ya existe para actualizarla
    while (actual != nullptr) {
        if (actual->clave == clave) {
            return;
        }
        actual = actual->sig;
    }

    // Paso B: Si no existe, insertar al frente (push_front)
    Nodo* nuevo = new Nodo(clave);
    nuevo->sig = tabla[idx];
    tabla[idx] = nuevo;
}

bool contiene(long long clave) {
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

int main() {
    int n;
    long long T;
    if (!(cin >> n >> T)) return 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        long long complemento = T - x;
        if (contiene(complemento) == true) {
            cout << "SI" << endl;
            return 0;
        }
        insertar(x);
    }
    cout << "NO" << endl;
    return 0;
}