#include <iostream>
using namespace std;

// 1. Nodo simple para guardar cada número
struct Nodo {
    int clave;
    int valor;
    Nodo* sig;
    Nodo(int c, int v) : clave(c), valor(v), sig(nullptr) {}
};

// 2. Tabla hash de tamaño primo grande
const int M = 1000003;
Nodo* tabla[M] = {nullptr};

// 3. Función hash por división (maneja negativos por seguridad)
int hash_func(int clave) {
    return ((clave % M) + M) % M;
}

void insertar (int clave) {
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

bool consumir_frecuencia (int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == clave) {
            if (actual->valor > 0) {
                actual->valor--;
                return true;
            }
            else {
                return false;
            }
        }
        actual = actual->sig;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. Leer A (Inventario)
    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        insertar(x); // Correcto: Guardamos A en la tabla
    }

    // 2. Leer tamaño de B (m) ANTES de comparar
    int m;
    if (!(cin >> m)) return 0;

    // Ahora sí podemos comparar
    if (n != m) {
        cout << "NO\n";
        return 0;
    }

    bool iguales = true;

    // 3. Leer B (Lista de compras) y solo consumir
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;

        // NO insertamos. Solo consumimos.
        if (consumir_frecuencia(x) == false) {
            iguales = false;
        }
    }

    // 4. Imprimir resultado
    if (iguales == false) {
        cout << "NO\n";
    }
    else {
        cout << "SI\n";
    }

    return 0;
}