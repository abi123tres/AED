#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Optimización estándar para acelerar la lectura de datos en C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // Leemos la cantidad de zonas (n) y la cantidad de puentes (m)
    if (!(cin >> n >> m)) return 0;

    // Arreglo para guardar el grado de cada vértice. 
    // Usamos tamaño n + 1 porque las zonas están numeradas del 1 al n.
    // Lo inicializamos todo en 0.
    vector<int> grado(n + 1, 0);

    // Leemos cada uno de los m puentes
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // Un puente conecta las zonas u y v, así que le sumamos 1 al grado de ambas.
        // OJO: Si u == v (es un lazo), el código sumará 1 a 'u' y luego 1 a 'v' (que es el mismo 'u'), 
        // sumando un total de 2 al grado de ese vértice, cumpliendo perfectamente la regla del problema.
        grado[u]++;
        grado[v]++;
    }

    // Variable para contar cuántas zonas tienen un grado (número de puentes) impar
    int zonas_impares = 0;

    // Revisamos el grado de todas las zonas (del 1 al n)
    for (int i = 1; i <= n; i++) {
        // El operador % 2 nos da el residuo de la división entre 2. 
        // Si no es 0, significa que el número es impar.
        if (grado[i] % 2 != 0) {
            zonas_impares++;
        }
    }

    // Aplicamos la regla matemática de los caminos Eulerianos
    if (zonas_impares == 0) {
        // Todos los vértices son pares
        cout << "CIRCUITO\n";
    } 
    else if (zonas_impares == 2) {
        // Exactamente dos vértices son impares (el inicio y el final)
        cout << "CAMINO\n";
    } 
    else {
        // Cualquier otra cantidad de vértices impares lo hace imposible
        cout << "IMPOSIBLE\n";
    }

    return 0;
}