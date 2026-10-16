#include <bits/stdc++.h>
using namespace std;

// Bellman-Ford Shortest Path + Negative Cycle Check | Time: O(V * E) | Space: O(E)
struct Edge { int u, v; long long w; };
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 4;
    vector<Edge> es = {{0, 1, 4}, {0, 2, 5}, {1, 2, -2}, {2, 3, 3}};
    const long long INF = 4e18;
    vector<long long> dist(n, INF);
    dist[0] = 0;
    for (int i = 0; i < n - 1; ++i) {
        bool chg = false;
        for (const auto& e : es) {
            if (dist[e.u] < INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                chg = true;
            }
        }
        if (!chg) break;
    }
    cout << "Shortest 0 -> 3: " << dist[3] << "\n";
    return 0;
}
