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

// Inserta una clave con su valor (o actualiza si ya existe)
void insertar(int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];

    // Paso A: Verificar si la clave ya existe para actualizarla
    while (actual != nullptr) {
        if (actual->clave == clave) {
            actual->valor += 1;
            return;
        }
        actual = actual->sig;
    }

    // Paso B: Si no existe, insertar al frente (push_front)
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        insertar(a[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (contar_frecuencia(a[i]) > n / 2) {
            cout << a[i] << "\n";
            delete[] a;
            return 0;
        }
    }

    cout << "NO EXISTE\n";
    delete[] a;
    return 0;
}