#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    // Optimización para leer datos masivos rápido (crucial para 200,000 líneas)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Arreglo para contar cuántos siguen a cada usuario (grado de entrada)
    // Tamaño n + 1 porque los usuarios están numerados del 1 al n.
    vector<int> in_degree(n + 1, 0);
    
    // Set para almacenar las aristas dirigidas {a, b}
    set<pair<int, int>> relaciones;
    
    int parejas_mutuas = 0;

    // Procesamos cada relación a -> b
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        
        // 1. El usuario 'b' gana un seguidor (aumenta su grado de entrada)
        in_degree[b]++;
        
        // 2. Comprobamos si existe la relación inversa (b -> a) en nuestro historial
        // .count() devuelve 1 si existe o 0 si no existe
        if (relaciones.count({b, a})) {
            parejas_mutuas++;
        }
        
        // 3. Guardamos la relación actual en el historial
        relaciones.insert({a, b});
    }

    // Variables para buscar al "influencer"
    int max_seguidores = -1;
    int usuario_top = -1;

    // Buscamos al usuario con más seguidores (iterando de 1 a n)
    for (int i = 1; i <= n; i++) {
        // Usamos '>' estricto. Si hay empate, la condición no se cumple y
        // nos quedamos con el primer usuario que alcanzó el máximo (el de menor número)
        if (in_degree[i] > max_seguidores) {
            max_seguidores = in_degree[i];
            usuario_top = i;
        }
    }

    // Imprimimos los 3 datos requeridos separados por espacio
    cout << parejas_mutuas << " " << usuario_top << " " << max_seguidores << "\n";

    return 0;
}