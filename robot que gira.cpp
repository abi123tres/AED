#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Nuestro estado ahora incluye hacia dónde mira el robot
struct Estado {
    int r, c, dir;
};

int main() {
    // Optimización de lectura (vital para matrices grandes)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // Movimientos según la dirección (0: Der, 1: Aba, 2: Izq, 3: Arr)
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};

    // Matriz de distancias 3D.
    // Usamos vector para evitar desbordamiento de pila (Stack Overflow)
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(4, -1)));

    // --- COLA MANUAL DE ALTO RENDIMIENTO ---
    // El tamaño máximo absoluto de estados es N * M * 4
    vector<Estado> q(n * m * 4);
    int head = 0;
    int tail = 0;

    // Inicializamos: Posición (0, 0), mirando a la derecha (dirección 0)
    dist[0][0][0] = 0;
    q[tail++] = {0, 0, 0}; // Push manual

    int respuesta = -1;

    while (head < tail) {
        Estado actual = q[head++]; // Pop manual

        int r = actual.r;
        int c = actual.c;
        int dir = actual.dir;
        int pasos = dist[r][c][dir];

        // Si llegamos a la celda de destino (n-1, m-1), guardamos la respuesta y terminamos
        if (r == n - 1 && c == m - 1) {
            respuesta = pasos;
            break;
        }

        // --- TRANSICIÓN 1: Avanzar (Mantiene la dirección, cambia la posición) ---
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        // Verificamos límites del mapa y que no sea una pared
        if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
            if (grid[nr][nc] != '#' && dist[nr][nc][dir] == -1) {
                dist[nr][nc][dir] = pasos + 1;
                q[tail++] = {nr, nc, dir};
            }
        }

        // --- TRANSICIÓN 2: Girar a la Izquierda (Mantiene posición, cambia dirección) ---
        int dir_izq = (dir + 3) % 4;
        if (dist[r][c][dir_izq] == -1) {
            dist[r][c][dir_izq] = pasos + 1;
            q[tail++] = {r, c, dir_izq};
        }

        // --- TRANSICIÓN 3: Girar a la Derecha (Mantiene posición, cambia dirección) ---
        int dir_der = (dir + 1) % 4;
        if (dist[r][c][dir_der] == -1) {
            dist[r][c][dir_der] = pasos + 1;
            q[tail++] = {r, c, dir_der};
        }
    }

    cout << respuesta << "\n";

    return 0;
}