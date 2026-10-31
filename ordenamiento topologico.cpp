#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    // Arreglo para contar cuántos prerrequisitos tiene cada nodo
    vector<int> in_degree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v; // Tarea 'u' debe ir antes que 'v'
        adj[u].push_back(v);
        in_degree[v]++; // 'v' gana un prerrequisito
    }

    vector<int> q(n + 1);
    int head = 0, tail = 0;

    // 1. Metemos a la cola todas las tareas que NO tienen prerrequisitos
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q[tail++] = i;
        }
    }

    vector<int> orden_final;

    // 2. Procesamos la cola
    while (head < tail) {
        int u = q[head++];
        orden_final.push_back(u); // Agregamos la tarea a nuestro orden resuelto

        // Al completar la tarea 'u', "liberamos" a sus vecinos
        for (int v : adj[u]) {
            in_degree[v]--; // Le restamos 1 prerrequisito a 'v'

            // Si 'v' ya no tiene prerrequisitos pendientes, lo metemos a la cola
            if (in_degree[v] == 0) {
                q[tail++] = v;
            }
        }
    }

    // Si logramos procesar las 'n' tareas, el orden es válido.
    // Si procesamos menos, significa que había un ciclo (ej: A requiere B y B requiere A).
    if (orden_final.size() == n) {
        for (int i = 0; i < n; i++) {
            cout << orden_final[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    } else {
        cout << "IMPOSIBLE (Hay un ciclo)\n";
    }

    return 0;
}