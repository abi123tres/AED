#include <iostream>

using namespace std;

// Estructura simple para representar un estado de las jarras
struct Estado {
    int a, b;

    // Función para comparar si dos estados son exactamente iguales
    bool es_igual(const Estado& otro) const {
        return a == otro.a && b == otro.b;
    }
};

// Función auxiliar para obtener el mínimo de dos números
int min_val(int val1, int val2) {
    return (val1 < val2) ? val1 : val2;
}

int main() {
    // Optimización vital para velocidad
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int A, B, X, Y;
    if (!(cin >> A >> B >> X >> Y)) return 0;

    long long total_aristas = 0;
    int grado_entrada = 0;

    // Recorremos todo el espacio de estados
    for (int a = 0; a <= A; ++a) {
        for (int b = 0; b <= B; ++b) {

            // Arreglo temporal para guardar los destinos de nuestras 6 jugadas
            Estado jugadas[6];
            int cantidad = 0;

            // 1. Llenar la primera
            jugadas[cantidad++] = {A, b};
            // 2. Llenar la segunda
            jugadas[cantidad++] = {a, B};
            // 3. Vaciar la primera
            jugadas[cantidad++] = {0, b};
            // 4. Vaciar la segunda
            jugadas[cantidad++] = {a, 0};
            // 5. Pasar de 1 a 2
            int m1 = min_val(a, B - b);
            jugadas[cantidad++] = {a - m1, b + m1};
            // 6. Pasar de 2 a 1
            int m2 = min_val(A - a, b);
            jugadas[cantidad++] = {a + m2, b - m2};

            // Arreglo para guardar los destinos que sí sean válidos y únicos
            Estado unicos[6];
            int unicos_cant = 0;

            // Filtramos las 6 jugadas
            for (int i = 0; i < cantidad; ++i) {
                Estado destino = jugadas[i];

                // Regla 1: Ignorar si la jugada no cambió el estado
                if (destino.a == a && destino.b == b) {
                    continue;
                }

                // Regla 2: Ignorar si esta jugada llevó a un estado repetido
                bool duplicado = false;
                for (int j = 0; j < unicos_cant; ++j) {
                    if (unicos[j].es_igual(destino)) {
                        duplicado = true;
                        break;
                    }
                }

                if (!duplicado) {
                    unicos[unicos_cant++] = destino;
                }
            }

            // Sumamos los caminos válidos únicos de este estado a nuestro total global
            total_aristas += unicos_cant;

            // Comprobamos si alguno de esos caminos lleva a nuestro destino objetivo (X, Y)
            for (int i = 0; i < unicos_cant; ++i) {
                if (unicos[i].a == X && unicos[i].b == Y) {
                    grado_entrada++;
                    // Rompemos porque desde el estado (a, b) ya confirmamos
                    // que hay al menos un puente hacia (X, Y)
                    break;
                }
            }
        }
    }

    cout << total_aristas << " " << grado_entrada << "\n";

    return 0;
}