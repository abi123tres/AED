#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    if (! (cin >> n)) return 0;
    vector<int> v(n +1);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int>dist(n + 1, -1);
    vector<int>q(n);
    q.push_back(1);
    dist[1] = 0;
    int head = 0;
    while (head < q.size()) {
        int u = q[head];
        if (u == n) {
            cout << dist[n];
            return 0;
        }
        int left = u - v[u];
        if (left = u - v[u]);
    }

}






















/*
q.push_back(1);
dist[1] = 0;
int head = 0;

while (head < (int)q.size()) {
int u = q[head++];

// Si ya llegamos a la meta, no necesitamos seguir explorando
if (u == n) {
cout << dist[u] << "\n";
return 0;
}

// Movimiento a la izquierda
int left = u - a[u];
if (left >= 1 && dist[left] == -1) {
dist[left] = dist[u] + 1;
q.push_back(left);
}

// Movimiento a la derecha
int right = u + a[u];
if (right <= n && dist[right] == -1) {
dist[right] = dist[u] + 1;
q.push_back(right);
}
}

// Si la cola se vacía y nunca llegamos a la piedra 'n'
cout << dist[n] << "\n";

return 0;
}*/