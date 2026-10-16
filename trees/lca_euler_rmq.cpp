#include <bits/stdc++.h>
using namespace std;

// LCA via Euler Tour + Sparse Table RMQ | Time: O(N log N) build, O(1) query
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 5;
    vector<vector<int>> adj(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(0, 2); edge(1, 3); edge(1, 4);
    vector<int> euler, depth, first_pos(n, -1);
    auto dfs = [&](auto& self, int u, int p, int d) -> void {
        if (first_pos[u] == -1) first_pos[u] = (int)euler.size();
        euler.push_back(u);
        depth.push_back(d);
        for (int v : adj[u]) {
            if (v != p) {
                self(self, v, u, d + 1);
                euler.push_back(u);
                depth.push_back(d);
            }
        }
    };
    dfs(dfs, 0, -1, 0);
    int m = (int)euler.size(), K = __lg(m) + 1;
    vector<vector<int>> st(K, vector<int>(m));
    iota(st[0].begin(), st[0].end(), 0);
    for (int k = 1; k < K; ++k)
        for (int i = 0; i + (1 << k) <= m; ++i) {
            int a = st[k - 1][i], b = st[k - 1][i + (1 << (k - 1))];
            st[k][i] = (depth[a] < depth[b]) ? a : b;
        }
    auto lca = [&](int u, int v) {
        int l = first_pos[u], r = first_pos[v];
        if (l > r) swap(l, r);
        int j = __lg(r - l + 1);
        int a = st[j][l], b = st[j][r - (1 << j) + 1];
        return euler[(depth[a] < depth[b]) ? a : b];
    };
    cout << "LCA(3, 4): " << lca(3, 4) << "\n";
    return 0;
}
