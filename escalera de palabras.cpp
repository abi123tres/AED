#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función para comparar dos palabras eficientemente
bool son_adyacentes(const string& w1, const string& w2, int L) {
    int diferencias = 0;
    for (int i = 0; i < L; ++i) {
        if (w1[i] != w2[i]) {
            diferencias++;
            // OPTIMIZACIÓN CLAVE: Si ya hay 2 o más diferencias, paramos.
            // Esto reduce drásticamente el tiempo de ejecución.
            if (diferencias > 1) {
                return false;
            }
        }
    }
    // Solo son adyacentes si difieren en exactamente 1 letra
    return diferencias == 1;
}

int main() {
    // Optimización de lectura y escritura (Crucial en programación competitiva)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, L;
    if (!(cin >> n >> L)) return 0;

    // Leer el diccionario de palabras
    vector<string> palabras(n);
    for (int i = 0; i < n; ++i) {
        cin >> palabras[i];
    }

    // Arreglo para guardar el grado (número de vecinos) de cada palabra
    vector<int> grado(n, 0);
    long long total_aristas = 0;

    // Doble bucle para comparar todos los pares posibles (i, j) sin repetirlos
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {

            // Si la regla se cumple, existe una arista (puente) entre ellas
            if (son_adyacentes(palabras[i], palabras[j], L)) {
                grado[i]++;
                grado[j]++;
                total_aristas++;
            }

        }
    }

    int max_grado = 0;
    int aisladas = 0;

    // Recorrido final para calcular las últimas dos métricas pedidas
    for (int i = 0; i < n; ++i) {
        if (grado[i] > max_grado) {
            max_grado = grado[i];
        }
        if (grado[i] == 0) {
            aisladas++;
        }
    }

    // Imprimir los 3 valores separados por un espacio
    cout << total_aristas << " " << max_grado << " " << aisladas << "\n";

    return 0;
}