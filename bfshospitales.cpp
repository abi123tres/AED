#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Optimización vital para leer cientos de miles de datos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    // Arreglo de distancias inicializado en -1
    // Tamaño n + 1 porque los pueblos van del 1 al n
    vector<int> dist(n + 1, -1);

    // --- IMPLEMENTACIÓN DE COLA MANUAL ---
    // Como máximo n vértices entrarán a la cola
    vector<int> q(n);
    int head = 0;
    int tail = 0;

    // 1. Leer los hospitales y meterlos TODOS a la cola al mismo tiempo
    for (int i = 0; i < k; i++) {
        int hospital;
        cin >> hospital;
        dist[hospital] = 0; // Un hospital está a distancia 0 de sí mismo
        q[tail++] = hospital; // Push manual
    }

    // 2. Construir la lista de adyacencia bidireccional
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Ejecutar BFS Multifuente
    while (head < tail) {
        int u = q[head++]; // Pop manual

        for (int v : adj[u]) {
            // Si el vecino no ha sido visitado (-1)
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1; // La distancia es la del padre + 1
                q[tail++] = v;         // Metemos el nuevo pueblo a la cola
            }
        }
    }

    // 4. Imprimir los resultados
    for (int i = 1; i <= n; i++) {
        cout << dist[i];
        // Imprimir espacio entre números, excepto en el último
        if (i < n) cout << " ";
    }
    cout << "\n";

    return 0;
}