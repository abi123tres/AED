#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs_multifuente(int n, vector<int>& origenes, vector<vector<int>>& adj) {
    vector<int> dist(n, -1);
    queue<int> q;

    // EL TRUCO: Insertar todas las fuentes en la cola ANTES del while
    for (int fuente : origenes) {
        dist[fuente] = 0;
        q.push(fuente);
    }

    // La propagación ocurre como múltiples ondas que se expanden a la vez
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}