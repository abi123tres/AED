#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // 1. Lectura de datos
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // 2. Arreglos para revisar vecinos (Arriba, Abajo, Izquierda, Derecha)
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // 3. Variables para almacenar las respuestas
    int perimetro_total = 0;
    vector<int> cantidad_por_grado(5, 0); // Índices del 0 al 4 inicializados en 0

    // 4. Recorrido total de la cuadrícula
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            
            // Solo nos interesan las casillas de tierra
            if (grid[r][c] == '#') {
                int vecinos_tierra = 0;

                // Revisar los 4 lados adyacentes
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    // Si el vecino está dentro del mapa y es tierra, sumamos al grado
                    if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                        if (grid[nr][nc] == '#') {
                            vecinos_tierra++;
                        }
                    }
                }

                // 5. Aplicar las reglas matemáticas del problema
                cantidad_por_grado[vecinos_tierra]++;
                perimetro_total += (4 - vecinos_tierra);
            }
        }
    }

    // 6. Imprimir el perímetro y luego el arreglo de frecuencias
    cout << perimetro_total;
    for (int k = 0; k <= 4; k++) {
        cout << " " << cantidad_por_grado[k];
    }
    cout << endl;

    return 0;
}