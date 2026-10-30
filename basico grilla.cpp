#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

// Arreglos de dirección: Arriba, Abajo, Izquierda, Derecha
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int bfs_grilla(vector<string>& grid, int inicio_r, int inicio_c, int fin_r, int fin_c) {
    int n = grid.size();
    int m = grid[0].size();

    // Matriz de distancias inicializada en -1
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    dist[inicio_r][inicio_c] = 0;
    q.push({inicio_r, inicio_c});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        // Si llegamos a la meta, retornamos la distancia
        if (r == fin_r && c == fin_c) {
            return dist[r][c];
        }

        // Probar las 4 direcciones
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // 1. No salir de los límites
            // 2. No pisar paredes ('#')
            // 3. No visitar celdas ya visitadas (dist == -1)
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                if (grid[nr][nc] != '#' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
    return -1; // No hay camino posible
}