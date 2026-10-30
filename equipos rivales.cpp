#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    // Optimización vital para lectura rápida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Lista de adyacencia
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Arreglo de colores: -1 (no visitado), 0 (Rojo), 1 (Azul)
    vector<int> color(n + 1, -1);

    // Cola manual para el BFS
    vector<int> q(n + 1);
    int head = 0;
    int tail = 0;

    int componentes_conexas = 0;
    bool es_posible = true;

    // Iteramos por todos los estudiantes porque el grafo puede estar desconectado
    for (int i = 1; i <= n; i++) {
        // Si el estudiante no tiene equipo (no ha sido visitado)
        if (color[i] == -1) {

            // Encontramos un nuevo grupo independiente
            componentes_conexas++;

            // Lanzamos un BFS desde este estudiante
            color[i] = 0; // Le asignamos el color 0
            q[tail++] = i; // Push manual

            while (head < tail) {
                int u = q[head++]; // Pop manual

                for (int v : adj[u]) {
                    // Si el rival no tiene equipo, lo metemos al equipo contrario
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q[tail++] = v;
                    }
                    // Si el rival YA tiene equipo, verificamos que no sea el mismo que el nuestro
                    else if (color[v] == color[u]) {
                        es_posible = false;
                        break;
                    }
                }
                if (!es_posible) break;
            }
        }
        if (!es_posible) break; // Detenemos todo si encontramos un conflicto
    }

    // Resultados
    if (!es_posible) {
        cout << "NO\n";
    } else {
        // Calculamos 2 elevado a la (cantidad de componentes conexas) aplicando módulo
        long long formas = 1;
        for (int i = 0; i < componentes_conexas; i++) {
            formas = (formas * 2) % MOD;
        }

        cout << "SI " << formas << "\n";
    }

    return 0;
}