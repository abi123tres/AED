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

bool contiene(int clave) {
    int idx = hash_func(clave);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == clave) {
            if (actual->valor > 0) {
                actual->valor = 0;
                return true;
            }
        }
        actual = actual->sig;
    }
    return false;
}

void swap_val(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void quicksort(int* arr, int izq, int der) {
    if (izq >= der) return;

    int pivote = arr[izq + (der - izq) / 2];
    int i = izq;
    int j = der;

    while (i <= j) {
        while (arr[i] < pivote) i++;
        while (arr[j] > pivote) j--;
        if (i <= j) {
            swap_val(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (izq < j) quicksort(arr, izq, j);
    if (i < der) quicksort(arr, i, der);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    int* resultado = new int[n];
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        insertar(x);
    }
    int m;
    if (!(cin >> m)) return 0;
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        if (contiene(x) == true) {
            resultado[k] = x;
            k++;
        }
    }
    quicksort(resultado, 0, k - 1);
    cout << k << "\n";
    for (int i = 0; i < k; ++i)
        cout << resultado[i] << " ";
    return 0;
}