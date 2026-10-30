#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs_basico(int n, int s, vector<vector<int>>& adj) {
    // n: cantidad de vértices, s: vértice inicial, adj: lista de adyacencia
    vector<int> dist(n, -1); // -1 significa "no visitado"
    queue<int> q;

    // Inicializar el origen
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Explorar vecinos
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1; // La distancia es la del padre + 1
                q.push(v);
            }
        }
    }
}

bool es_bipartito(int n, vector<vector<int>>& adj) {
    vector<int> color(n, -1); // -1: sin color, 0: color A, 1: color B

    // Bucle extra por si el grafo está desconectado en varias componentes
    for (int i = 0; i < n; i++) {
        if (color[i] != -1) continue; // Ya fue coloreado en otro BFS

        queue<int> q;
        color[i] = 0;
        q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (color[v] == -1) {
                    // Si no tiene color, se le asigna el color opuesto al padre (1 - 0 = 1, 1 - 1 = 0)
                    color[v] = 1 - color[u];
                    q.push(v);
                }
                else if (color[v] == color[u]) {
                    // Conflicto: dos nodos conectados tienen el mismo color (ciclo impar)
                    return false;
                }
            }
        }
    }
    return true; // Se logró colorear sin conflictos
}
void contar_caminos(int n, int s, vector<vector<int>>& adj) {
    vector<int> dist(n, -1);
    vector<int> cnt(n, 0); // Arreglo para contar caminos
    queue<int> q;

    dist[s] = 0;
    cnt[s] = 1; // Solo hay 1 forma de llegar al inicio (quedarse parado)
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                // CASO A: Vértice descubierto por primera vez
                dist[v] = dist[u] + 1;
                cnt[v] = cnt[u];       // Hereda la cantidad de caminos del padre
                q.push(v);
            }
            else if (dist[v] == dist[u] + 1) {
                // CASO B: Vértice ya descubierto, pero encontramos OTRA ruta igual de corta
                // Sumamos los caminos del nuevo ancestro
                cnt[v] += cnt[u];
            }
        }
    }
}