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

void buscar(int clave) {

    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == clave) {
            cout << actual->valor << "\n";
            return;
        }
        actual = actual->sig;
    }
    cout << "NO EXISTE" << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; i++) {
        string instruccion;
        if (!(cin >> instruccion)) return 0;
        if (instruccion == "INSERTAR") {
            int k, v;
            if (!(cin >> k >> v)) return 0;
            insertar(k, v);
        }
        else if (instruccion == "ELIMINAR") {
            int k;
            if (!(cin >> k)) return 0;
            eliminar(k);
        }
        else {
            int k;
            if (!(cin >> k)) return 0;
            buscar(k);
        }
    }
    return 0;
}