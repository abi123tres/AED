#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Optimización de lectura
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Leemos el estado inicial y lo convertimos a un solo número entero (Bitmask)
    int estado_inicial = 0;
    for (int i = 0; i < n; i++) {
        string fila;
        cin >> fila;
        for (int j = 0; j < m; j++) {
            if (fila[j] == '1') {
                // Calculamos en qué posición (del 0 al 15) está este foco
                int posicion_bit = i * m + j;
                // Encendemos ese bit en nuestro número entero usando OR y Shift
                estado_inicial |= (1 << posicion_bit);
            }
        }
    }

    // El estado ganador es tener todas las luces apagadas (el número 0)
    if (estado_inicial == 0) {
        cout << 0 << "\n";
        return 0;
    }

    // Movimientos para afectar a la celda actual y sus 4 vecinos
    // Incluimos el (0,0) para que el foco presionado también cambie de estado
    int dr[] = {0, -1, 1, 0, 0};
    int dc[] = {0, 0, 0, -1, 1};

    // --- COLA MANUAL PARA BFS DE ESTADOS ---
    // Tamaño máximo absoluto: 2 elevado a la (n * m). En el peor caso 2^16 = 65536.
    int max_estados = 1 << (n * m);
    vector<int> dist(max_estados, -1);

    vector<int> q(max_estados);
    int head = 0;
    int tail = 0;

    // Inicializamos
    dist[estado_inicial] = 0;
    q[tail++] = estado_inicial; // Push manual

    while (head < tail) {
        int estado_actual = q[head++]; // Pop manual

        // Vamos a simular que presionamos cada uno de los (n * m) focos del tablero
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {

                int nuevo_estado = estado_actual;

                // Al presionar (r, c), se afectan él mismo y sus vecinos válidos
                for (int i = 0; i < 5; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    // Si el vecino está dentro del tablero
                    if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                        int pos_bit = nr * m + nc;
                        // Usamos XOR (^) para cambiar el estado de ese foco específico
                        nuevo_estado ^= (1 << pos_bit);
                    }
                }

                // Verificamos si este nuevo tablero ya lo habíamos visto antes
                if (dist[nuevo_estado] == -1) {
                    dist[nuevo_estado] = dist[estado_actual] + 1;

                    // Si logramos apagar todas las luces, imprimimos y terminamos inmediatamente
                    if (nuevo_estado == 0) {
                        cout << dist[nuevo_estado] << "\n";
                        return 0;
                    }

                    // Si no, lo metemos a la cola para seguir buscando
                    q[tail++] = nuevo_estado;
                }
            }
        }
    }

    // Si la cola se vació y nunca llegamos al estado 0 (todas apagadas)
    cout << -1 << "\n";

    return 0;
}