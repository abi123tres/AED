#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Celda {
    int r, c;
};

int main() {
    // Optimización vital para 1000x1000
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Matriz de distancias, inicializada en un número gigante (infinito)
    // 1e9 es 1,000,000,000
    const int INF = 1e9;
    vector<vector<int>> dist(n, vector<int>(m, INF));

    // --- IMPLEMENTACIÓN DE BIDECOLA MANUAL (DEQUE) ---
    // El tamaño máximo que puede ocupar es N*M, pero como crece hacia ambos
    // lados, le damos el doble de tamaño.
    int max_size = n * m;
    vector<Celda> dq(2 * max_size);
    
    // Iniciamos los punteros exactamente en el centro del arreglo
    int head = max_size;
    int tail = max_size;

    // Inicializamos la coordenada de inicio
    dist[0][0] = 0;
    dq[tail++] = {0, 0}; // Push_back inicial

    while (head < tail) {
        // Sacamos el elemento del frente (Pop_front)
        Celda actual = dq[head++];
        int r = actual.r;
        int c = actual.c;

        // Explorar los 4 vecinos
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                // Si es pared el costo es 1, si es libre el costo es 0
                int costo = (grid[nr][nc] == '#') ? 1 : 0;

                // Relajación: Si encontramos un camino MÁS BARATO hacia esta casilla
                if (dist[r][c] + costo < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + costo;

                    // APLICAMOS LA REGLA DEL BFS 0-1
                    if (costo == 0) {
                        // Cuesta 0: Metemos al FRENTE de la cola (Push_front manual)
                        // Restamos 1 a la cabeza antes de guardar
                        head--;
                        dq[head] = {nr, nc};
                    } else {
                        // Cuesta 1: Metemos al FINAL de la cola (Push_back manual)
                        // Guardamos y luego sumamos 1 a la cola
                        dq[tail] = {nr, nc};
                        tail++;
                    }
                }
            }
        }
    }

    // La meta siempre es la esquina inferior derecha (n-1, m-1)
    cout << dist[n - 1][m - 1] << "\n";

    return 0;
}