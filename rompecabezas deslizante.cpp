#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. Leemos el tablero inicial y lo convertimos en un solo número entero
    int estado_inicial = 0;
    for (int i = 0; i < 6; i++) {
        int x;
        if (!(cin >> x)) return 0;
        estado_inicial = estado_inicial * 10 + x;
    }

    // El estado ganador que buscamos (1 2 3 / 4 5 0)
    int estado_objetivo = 123450;

    // Caso borde: Si ya nos dan el tablero resuelto
    if (estado_inicial == estado_objetivo) {
        cout << 0 << "\n";
        return 0;
    }

    // Arreglo de distancias. El número máximo posible es 543210.
    // Con 600,000 nos sobra espacio. Todo inicializado en -1 (No visitado).
    vector<int> dist(600000, -1);

    // --- COLA MANUAL ---
    // Como solo hay 720 combinaciones posibles, 1000 espacios es más que suficiente
    vector<int> q(1000);
    int head = 0;
    int tail = 0;

    // Inicializamos BFS
    dist[estado_inicial] = 0;
    q[tail++] = estado_inicial;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (head < tail) {
        int estado_actual = q[head++];

        // Si encontramos la solución, la imprimimos y terminamos
        if (estado_actual == estado_objetivo) {
            cout << dist[estado_actual] << "\n";
            return 0;
        }

        // --- DESEMPAQUETAR ---
        // Convertimos el entero de vuelta a una matriz 2x3
        int tablero[2][3];
        int temp = estado_actual;
        int fila_cero = -1, col_cero = -1;

        // Extraemos los dígitos de derecha a izquierda (de atrás hacia adelante)
        for (int r = 1; r >= 0; r--) {
            for (int c = 2; c >= 0; c--) {
                tablero[r][c] = temp % 10;
                if (tablero[r][c] == 0) {
                    fila_cero = r;
                    col_cero = c;
                }
                temp /= 10;
            }
        }

        // --- GENERAR MOVIMIENTOS ---
        for (int i = 0; i < 4; i++) {
            int nr = fila_cero + dr[i];
            int nc = col_cero + dc[i];

            // Si el movimiento está dentro del tablero
            if (nr >= 0 && nr < 2 && nc >= 0 && nc < 3) {

                // Intercambiamos el 0 con el número adyacente (Swap manual)
                int numero_vecino = tablero[nr][nc];
                tablero[fila_cero][col_cero] = numero_vecino;
                tablero[nr][nc] = 0;

                // --- EMPAQUETAR ---
                // Convertimos la matriz modificada de vuelta a un entero
                int nuevo_estado = 0;
                for (int r = 0; r < 2; r++) {
                    for (int c = 0; c < 3; c++) {
                        nuevo_estado = nuevo_estado * 10 + tablero[r][c];
                    }
                }

                // Deshacemos el movimiento en la matriz original para el siguiente ciclo del 'for'
                tablero[nr][nc] = numero_vecino;
                tablero[fila_cero][col_cero] = 0;

                // Si este nuevo estado no ha sido visitado (-1), lo procesamos
                if (dist[nuevo_estado] == -1) {
                    dist[nuevo_estado] = dist[estado_actual] + 1;
                    q[tail++] = nuevo_estado;
                }
            }
        }
    }

    // Si se agotan las combinaciones y nunca llegamos al estado objetivo
    cout << -1 << "\n";

    return 0;
}