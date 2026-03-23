#include <bits/stdc++.h>
using namespace std;

// Tree Distance via Binary Lifting LCA | Time: O(N log N) build, O(log N) query
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 5, LOG = 4;
    vector<vector<int>> adj(n), up(LOG, vector<int>(n, -1));
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(0, 2); edge(1, 3); edge(1, 4);
    vector<int> depth(n, 0);
    auto dfs = [&](auto& self, int u, int p) -> void {
        up[0][u] = p;
        for (int k = 1; k < LOG; ++k) up[k][u] = (up[k - 1][u] == -1) ? -1 : up[k - 1][up[k - 1][u]];
        for (int v : adj[u]) if (v != p) { depth[v] = depth[u] + 1; self(self, v, u); }
    };
    dfs(dfs, 0, -1);
    auto lca = [&](int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int k = 0; k < LOG; ++k) if ((diff >> k) & 1) u = up[k][u];
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; --k) if (up[k][u] != up[k][v]) { u = up[k][u]; v = up[k][v]; }
        return up[0][u];
    };
    cout << "Dist(3, 4): " << (depth[3] + depth[4] - 2 * depth[lca(3, 4)]) << "\n";
    return 0;
}
