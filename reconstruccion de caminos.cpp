#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, -1);
    // Arreglo vital para reconstruir la ruta. 
    // Guardará "desde qué nodo llegué a este nodo".
    vector<int> padre(n + 1, -1); 
    
    vector<int> q(n + 1);
    int head = 0, tail = 0;

    // Iniciamos en el nodo 1
    dist[1] = 0;
    q[tail++] = 1;

    while (head < tail) {
        int u = q[head++];

        if (u == n) break; // Llegamos a la meta

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                padre[v] = u; // "El nodo 'v' fue descubierto por el nodo 'u'"
                q[tail++] = v;
            }
        }
    }

    if (dist[n] == -1) {
        cout << "IMPOSIBLE\n";
    } else {
        // Reconstruimos el camino leyendo las "migas de pan" de atrás hacia adelante
        vector<int> camino;
        int actual = n;
        
        while (actual != -1) {
            camino.push_back(actual);
            actual = padre[actual]; // Retrocedemos al padre
        }

        // Como el camino se guardó desde la meta hasta el inicio, 
        // lo imprimimos recorriendo el vector al revés (sin usar reverse de <algorithm>)
        cout << camino.size() << "\n"; // Cantidad de nodos en la ruta
        for (int i = (int)camino.size() - 1; i >= 0; i--) {
            cout << camino[i] << (i == 0 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}