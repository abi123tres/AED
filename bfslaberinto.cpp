#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Celda {
    int r, c;
};

int main() {
    // Optimización de lectura (crucial para matrices de 1000x1000)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    int inicio_r = -1, inicio_c = -1;
    int fin_r = -1, fin_c = -1;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                inicio_r = i;
                inicio_c = j;
            } else if (grid[i][j] == 'E') {
                fin_r = i;
                fin_c = j;
            }
        }
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    vector<vector<int>> dist(n, vector<int>(m, -1));

    // --- IMPLEMENTACIÓN DE COLA MANUAL ---
    // El tamaño máximo que puede alcanzar la cola es todas las casillas (n * m)
    vector<Celda> q(n * m);
    int head = 0; // Apunta al elemento que vamos a sacar
    int tail = 0; // Apunta al espacio vacío donde vamos a insertar

    // 4. Inicializamos el BFS (Push manual)
    dist[inicio_r][inicio_c] = 0;
    q[tail] = {inicio_r, inicio_c};
    tail++; // Avanzamos la cola

    // Mientras la cola no esté vacía
    while (head < tail) {

        // Front y Pop manuales
        Celda actual = q[head];
        head++; // Avanzamos la cabeza

        // Si llegamos a la salida, detenemos la búsqueda
        if (actual.r == fin_r && actual.c == fin_c) {
            break;
        }

        // 5. Explorar los 4 vecinos
        for (int i = 0; i < 4; i++) {
            int nr = actual.r + dr[i];
            int nc = actual.c + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                if (grid[nr][nc] != '#' && dist[nr][nc] == -1) {

                    dist[nr][nc] = dist[actual.r][actual.c] + 1;

                    // Push manual del vecino
                    q[tail] = {nr, nc};
                    tail++;
                }
            }
        }
    }

    cout << dist[fin_r][fin_c] << "\n";

    return 0;
}