#include <iostream>

using namespace std;

// 1. Nodo simple para guardar cada número
struct Nodo {
    int clave;
    Nodo* sig;
    Nodo(int c) : clave(c), sig(nullptr) {}
};

// 2. Tabla hash de tamaño primo grande
const int M = 1000003;
Nodo* tabla[M] = {nullptr};

// 3. Función hash por división (maneja negativos por seguridad)
int hash_func(int clave) {
    return ((clave % M) + M) % M;
}

bool insertar_noRepetido (int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];

    // Paso A: Verificar si la clave ya existe para actualizarla
    while (actual != nullptr) {
        if (actual->clave == clave) {
            return false;
        }
        actual = actual->sig;
    }

    // Paso B: Si no existe, insertar al frente (push_front)
    Nodo* nuevo = new Nodo(clave);
    nuevo->sig = tabla[idx];
    tabla[idx] = nuevo;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int distintos = 0;
    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (insertar_noRepetido(a[i])) {
            distintos++;
        }
    }
    cout << distintos;
    return 0;
}