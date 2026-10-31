#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> dist(n + 1, -1);

    vector<int> q;
    q.reserve(n);

    q.push_back(1);
    dist[1] = 0;
    int head = 0;

    while (head < (int)q.size()) {
        int u = q[head++];

        if (u == n) {
            cout << dist[u] << "\n";
            return 0;
        }

        int left = u - a[u];
        if (left >= 1 && dist[left] == -1) {
            dist[left] = dist[u] + 1;
            q.push_back(left);
        }

        int right = u + a[u];
        if (right <= n && dist[right] == -1) {
            dist[right] = dist[u] + 1;
            q.push_back(right);
        }
    }

    cout << dist[n] << "\n";

    return 0;
}