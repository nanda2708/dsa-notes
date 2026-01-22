#include <bits/stdc++.h>
using namespace std;

// Tree Height & Subtree Size | Time: O(N) | Space: O(N)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 5;
    vector<vector<int>> adj(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(0, 2); edge(1, 3); edge(1, 4);
    vector<int> sz(n, 1), h(n, 0);
    auto dfs = [&](auto& self, int u, int p) -> void {
        for (int v : adj[u]) if (v != p) {
            self(self, v, u);
            sz[u] += sz[v];
            h[u] = max(h[u], h[v] + 1);
        }
    };
    dfs(dfs, 0, -1);
    cout << "Height: " << h[0] << ", Subtree(1): " << sz[1] << "\n";
    return 0;
}
