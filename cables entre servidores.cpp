#include <iostream>
#include <vector>

using namespace std;

// Estructura simple para guardar las consultas
struct Consulta {
    int destino;
    int indice_original; // Para recordar en qué orden nos hicieron la pregunta
};

int main() {
    // Optimización vital para leer 200,000 líneas rápido
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    // 1. Grafo: lista de adyacencia para los cables
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // Normalizamos: el menor siempre es 'u', el mayor es 'v'
        if (u > v) swap(u, v); // swap es nativo, no requiere <algorithm>

        adj[u].push_back(v);
    }

    // 2. Grafo de preguntas: guardamos qué nos preguntan de cada nodo
    vector<vector<Consulta>> preguntas(n + 1);

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        // Normalizamos la pregunta igual que los cables
        if (u > v) swap(u, v);

        // Guardamos que al nodo 'u' le preguntan por 'v', en el turno 'i'
        Consulta actual;
        actual.destino = v;
        actual.indice_original = i;
        preguntas[u].push_back(actual);
    }

    // Arreglo para guardar las respuestas en el orden correcto
    vector<int> respuestas(q);

    // Arreglo temporal de conteo rápido (iniciado en 0)
    vector<int> cables_conectados(n + 1, 0);

    // 3. Procesamiento Offline (La magia matemática)
    for (int u = 1; u <= n; u++) {

        // PASO A: "Encender" los cables conectados a 'u'
        // Si hay 3 cables hacia el servidor 5, cables_conectados[5] valdrá 3
        for (int v : adj[u]) {
            cables_conectados[v]++;
        }

        // PASO B: Responder todas las preguntas relacionadas a 'u' en O(1)
        for (Consulta pregunta : preguntas[u]) {
            int destino = pregunta.destino;
            int indice = pregunta.indice_original;

            // La respuesta es exactamente lo que dice nuestro contador
            respuestas[indice] = cables_conectados[destino];
        }

        // PASO C: "Apagar" y limpiar el contador para el siguiente nodo
        // Hacemos esto recorriendo los mismos vecinos, es más rápido que limpiar todo el arreglo
        for (int v : adj[u]) {
            cables_conectados[v] = 0;
        }
    }

    // 4. Imprimir las respuestas en el orden exacto en que las pidieron
    for (int i = 0; i < q; i++) {
        cout << respuestas[i] << "\n";
    }

    return 0;
}