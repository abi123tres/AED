#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Optimización de lectura masiva
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Listas de adyacencia para el Grafo Original y el Grafo Transpuesto
    vector<vector<int>> adj_out(n + 1); // A quiénes sigo (Grafo original)
    vector<vector<int>> adj_in(n + 1);  // Quiénes me siguen (Grafo transpuesto)

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj_out[a].push_back(b); // 'a' sigue a 'b'
        adj_in[b].push_back(a);  // 'b' es seguido por 'a'
    }

    int parejas_mutuas = 0;

    // Arreglo booleano temporal para marcar relaciones en O(1)
    vector<bool> marcado(n + 1, false);

    // 1. Contar Parejas Mutuas usando teoría de grafos
    for (int u = 1; u <= n; u++) {
        // Paso A: Marcar a todos los usuarios que 'u' sigue
        for (int v : adj_out[u]) {
            marcado[v] = true;
        }

        // Paso B: Revisar a todos los que siguen a 'u'.
        // Si están marcados, el seguimiento es mutuo.
        for (int v : adj_in[u]) {
            if (marcado[v] == true) {
                parejas_mutuas++;
            }
        }

        // Paso C: Desmarcar (limpiar) para no afectar la búsqueda del siguiente usuario
        for (int v : adj_out[u]) {
            marcado[v] = false;
        }
    }

    // Dividimos entre 2 porque cada pareja {A, B} se contó al revisar A y al revisar B
    parejas_mutuas = parejas_mutuas / 2;

    // 2. Buscar al usuario con mayor grado de entrada (más seguidores)
    int max_seguidores = -1;
    int usuario_top = -1;

    for (int i = 1; i <= n; i++) {
        // El grado de entrada es simplemente el tamaño de su lista en el Grafo Transpuesto
        int seguidores = adj_in[i].size();

        // Usamos '>' estricto para que gane el de menor número en caso de empate
        if (seguidores > max_seguidores) {
            max_seguidores = seguidores;
            usuario_top = i;
        }
    }

    cout << parejas_mutuas << " " << usuario_top << " " << max_seguidores << "\n";

    return 0;
}