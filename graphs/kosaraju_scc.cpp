#include <bits/stdc++.h>
using namespace std;

// Kosaraju Two-Pass SCC | Time: O(V + E) | Space: O(V + E)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 5;
    vector<vector<int>> adj(n), rev(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); rev[v].push_back(u); };
    edge(0, 2); edge(2, 1); edge(1, 0); edge(0, 3); edge(3, 4);
    vector<int> vis(n, 0), ord;
    auto dfs1 = [&](auto& self, int u) -> void {
        vis[u] = 1;
        for (int v : adj[u]) if (!vis[v]) self(self, v);
        ord.push_back(u);
    };
    for (int i = 0; i < n; ++i) if (!vis[i]) dfs1(dfs1, i);
    fill(vis.begin(), vis.end(), 0);
    reverse(ord.begin(), ord.end());
    int sccs = 0;
    auto dfs2 = [&](auto& self, int u) -> void {
        vis[u] = 1;
        for (int v : rev[u]) if (!vis[v]) self(self, v);
    };
    for (int u : ord) if (!vis[u]) { ++sccs; dfs2(dfs2, u); }
    cout << "Total SCCs: " << sccs << "\n";
    return 0;
}
