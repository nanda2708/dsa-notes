#include <bits/stdc++.h>
using namespace std;

// Prim's MST Algorithm | Time: O((V + E) log V) | Space: O(V + E)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 4;
    vector<vector<pair<int, int>>> adj(n);
    auto edge = [&](int u, int v, int w) { adj[u].push_back({v, w}); adj[v].push_back({u, w}); };
    edge(0, 1, 10); edge(0, 2, 6); edge(0, 3, 5); edge(1, 3, 15); edge(2, 3, 4);
    vector<int> vis(n, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});
    long long mst = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = 1; mst += w;
        for (auto [v, nw] : adj[u]) if (!vis[v]) pq.push({nw, v});
    }
    cout << "Prim MST: " << mst << "\n";
    return 0;
}
