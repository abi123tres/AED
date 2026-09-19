#include <iostream>
#include <vector>
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
            actual->valor++;
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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;

    if (!(cin >> n)) return 0;
    n = n*n;
    vector<int> A(n), B(n), C(n), D(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    for (int i = 0; i < n; i++) cin >> C[i];
    for (int i = 0; i < n; i++) cin >> D[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            insertar(A[i]+ B[j]);

    int cuad = 0;
    for (int k = 0; k < n; k++)
        for (int l = 0; l < n; l++) {
            int objetivo = -(C[k] + D[l]);
            cuad += contar_frecuencia(objetivo);
        }
    cout << cuad << endl;
    return 0;
}












int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> A(n), B(n), C(n), D(n);

    for (int i = 0; i < n; ++i) cin >> A[i];
    for (int i = 0; i < n; ++i) cin >> B[i];
    for (int i = 0; i < n; ++i) cin >> C[i];
    for (int i = 0; i < n; ++i) cin >> D[i];

    // 1. Guardar todas las sumas de A[i] + B[j] en la tabla Hash
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            insertar(A[i] + B[j]);
        }
    }

    // 2. Contar combinaciones donde A[i] + B[j] == -(C[k] + D[l])
    long long total_cuadruplas = 0;
    for (int k = 0; k < n; ++k) {
        for (int l = 0; l < n; ++l) {
            int objetivo = -(C[k] + D[l]);
            total_cuadruplas += contar_frecuencia(objetivo);
        }
    }

    cout << total_cuadruplas << "\n";

    return 0;
}