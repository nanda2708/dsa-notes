#include <bits/stdc++.h>
using namespace std;

// Tree Centroid Finder | Time: O(N) | Space: O(N)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 6;
    vector<vector<int>> adj(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(1, 2); edge(2, 3); edge(2, 4); edge(4, 5);
    vector<int> sz(n, 1);
    auto dfs = [&](auto& self, int u, int p) -> void {
        for (int v : adj[u]) if (v != p) { self(self, v, u); sz[u] += sz[v]; }
    };
    dfs(dfs, 0, -1);
    auto find_c = [&](auto& self, int u, int p) -> int {
        for (int v : adj[u]) if (v != p && sz[v] > n / 2) return self(self, v, u);
        return u;
    };
    cout << "Centroid: " << find_c(find_c, 0, -1) << "\n";
    return 0;
}
