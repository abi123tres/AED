#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    if (! (cin >> n >> m)) return 0;
    if (m != n - 1) {
        cout << "NO";
        return 0;
    }
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for (int i = 1; i < m - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 2) {
            cout << "NO";
            return 0;
        }
    }
    vector<bool>visited(n + 1, false);
    int start = 1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] <= 1) {
            start = 1;
            break;
        }
    }
    int curr = start;
    int prev = 0;
    int visitados = 0;
    while (curr != 0) {
        visitados++;
        int sig = 0;
        for (int v : adj[curr]) {
            if (v == prev) {
                sig = v;
                break;
            }
        }
        prev = curr;
        curr = sig;
    }
    if (visitados == n)
        cout << "SI";
    else
        cout << "NO";
    return 0;
}