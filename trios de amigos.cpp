#include <iostream>
#include <vector>

using namespace std;

// Declaramos la matriz globalmente para que se inicialice sola en 'false'
// Tamaño 3005 porque n llega hasta 3000. (Las variables globales van en el segmento BSS y no saturan la pila)
bool es_amigo[3005][3005];

int main() {
    // Optimización de lectura (obligatoria en problemas de tiempo corto)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Lista de adyacencia dirigida
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        // 1. En la matriz, marcamos la amistad en ambas direcciones
        // para poder consultarla rápido al final
        es_amigo[u][v] = true;
        es_amigo[v][u] = true;

        // 2. En la lista, SOLO guardamos la arista del menor al mayor
        // Esto fuerza el orden u < v < w y evita contar tríos repetidos
        if (u < v) {
            adj[u].push_back(v);
        } else {
            adj[v].push_back(u);
        }
    }

    long long total_trios = 0;

    // 3. Búsqueda de triángulos (u -> v -> w)
    for (int u = 1; u <= n; u++) {
        // Recorremos los amigos 'v' que son mayores que 'u'
        for (int v : adj[u]) {

            // Recorremos los amigos 'w' que son mayores que 'v'
            for (int w : adj[v]) {

                // Ya sabemos que u es amigo de v, y v es amigo de w.
                // Solo falta revisar si el triángulo se cierra verificando si u es amigo de w.
                // Esta consulta toma O(1) gracias a la matriz booleana.
                if (es_amigo[u][w] == true) {
                    total_trios++;
                }
            }
        }
    }

    // Imprimir el número total de tríos
    cout << total_trios << "\n";

    return 0;
}