#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Optimización vital para 200,000 líneas de entrada
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    // Grafo no dirigido
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // La amistad es mutua
    }

    // Arreglo booleano global para marcar amigos rápidamente en O(1)
    vector<bool> es_amigo(n + 1, false);

    // Procesamos cada pregunta
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;

        int comunes = 0;

        // PASO 1: Marcar a todos los amigos de 'u'
        for (int amigo : adj[u]) {
            es_amigo[amigo] = true;
        }

        // PASO 2: Revisar si los amigos de 'v' están marcados
        for (int amigo : adj[v]) {
            if (es_amigo[amigo] == true) {
                comunes++;
            }
        }

        // PASO 3: Desmarcar a los amigos de 'u' para que el arreglo
        // quede limpio (todo en false) para la siguiente pregunta.
        // OJO: Solo iteramos sobre adj[u], no sobre los N usuarios.
        for (int amigo : adj[u]) {
            es_amigo[amigo] = false;
        }

        // Imprimir la respuesta de esta consulta
        cout << comunes << "\n";
    }

    return 0;
}