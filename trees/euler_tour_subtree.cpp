#include <bits/stdc++.h>
using namespace std;

// Euler Tour Subtree Flattening | Time: O(N) | Space: O(N)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 5;
    vector<vector<int>> adj(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(0, 2); edge(1, 3); edge(1, 4);
    vector<int> tin(n), tout(n);
    int timer = 0;
    auto dfs = [&](auto& self, int u, int p) -> void {
        tin[u] = timer++;
        for (int v : adj[u]) if (v != p) self(self, v, u);
        tout[u] = timer - 1;
    };
    dfs(dfs, 0, -1);
    cout << "Subtree 1: [" << tin[1] << ", " << tout[1] << "]\n";
    return 0;
}
