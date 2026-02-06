#include <bits/stdc++.h>
using namespace std;

// Undirected Graph Cycle Detection | Time: O(V + E) | Space: O(V)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 4;
    vector<vector<int>> adj(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(1, 2); edge(2, 3); edge(3, 1);
    vector<int> vis(n, 0);
    bool has_cycle = false;
    auto dfs = [&](auto& self, int u, int p) -> void {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!vis[v]) self(self, v, u);
            else if (v != p) has_cycle = true;
        }
    };
    for (int i = 0; i < n; ++i) if (!vis[i]) dfs(dfs, i, -1);
    cout << "Has cycle: " << (has_cycle ? "Yes" : "No") << "\n";
    return 0;
}
