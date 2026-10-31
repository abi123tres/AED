#include <iostream>
#include <vector>

using namespace std;

// Función para no repetir código. Retorna el nodo más lejano descubierto.
// Pasamos 'dist' por referencia para poder leer las distancias calculadas al terminar.
int lanzar_bfs(int inicio, int n, const vector<vector<int>>& adj, vector<int>& dist) {
    // Limpiamos el arreglo de distancias
    for (int i = 1; i <= n; i++) dist[i] = -1;

    vector<int> q(n + 1);
    int head = 0, tail = 0;

    dist[inicio] = 0;
    q[tail++] = inicio;

    int nodo_mas_lejano = inicio;
    int max_distancia = 0;

    while (head < tail) {
        int u = q[head++];

        // Guardamos rastro del nodo que alcanzó la mayor distancia
        if (dist[u] > max_distancia) {
            max_distancia = dist[u];
            nodo_mas_lejano = u;
        }

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q[tail++] = v;
            }
        }
    }

    return nodo_mas_lejano;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // En un árbol de N nodos, siempre hay exactamente N-1 aristas
    if (!(cin >> n)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1);

    // PASO 1: BFS desde un nodo cualquiera (ej. 1) para hallar un extremo del diámetro (Punto A)
    int extremo_A = lanzar_bfs(1, n, adj, dist);

    // PASO 2: BFS desde el Punto A. El nodo más lejano será el Punto B (el otro extremo).
    int extremo_B = lanzar_bfs(extremo_A, n, adj, dist);

    // La distancia almacenada en el Punto B es el Diámetro del Árbol
    cout << dist[extremo_B] << "\n";

    return 0;
}