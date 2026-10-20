#include <bits/stdc++.h>
using namespace std;

// Heavy-Light Decomposition + Fenwick Path Sum | Time: O(log^2 N) | Space: O(N)
struct BIT {
    int n; vector<long long> bit;
    BIT(int n) : n(n), bit(n + 1, 0) {}
    void add(int i, long long v) { for (++i; i <= n; i += i & -i) bit[i] += v; }
    long long sum(int i) const { long long s = 0; for (++i; i > 0; i -= i & -i) s += bit[i]; return s; }
    long long range(int l, int r) const { return l > r ? 0 : sum(r) - (l ? sum(l - 1) : 0); }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 5;
    vector<vector<int>> adj(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(0, 2); edge(1, 3); edge(1, 4);
    vector<long long> val = {1, 2, 3, 4, 5};
    vector<int> par(n, -1), dep(n, 0), sz(n, 1), hvy(n, -1), head(n), pos(n);
    auto dfs1 = [&](auto& self, int u, int p, int d) -> void {
        par[u] = p; dep[u] = d; sz[u] = 1; int best = 0;
        for (int v : adj[u]) if (v != p) { self(self, v, u, d + 1); sz[u] += sz[v]; if (sz[v] > best) { best = sz[v]; hvy[u] = v; } }
    };
    dfs1(dfs1, 0, -1, 0);
    int cur = 0;
    auto dfs2 = [&](auto& self, int u, int h) -> void {
        head[u] = h; pos[u] = cur++;
        if (hvy[u] != -1) self(self, hvy[u], h);
        for (int v : adj[u]) if (v != par[u] && v != hvy[u]) self(self, v, v);
    };
    dfs2(dfs2, 0, 0);
    BIT bit(n); for (int i = 0; i < n; ++i) bit.add(pos[i], val[i]);
    auto path_sum = [&](int a, int b) {
        long long res = 0;
        while (head[a] != head[b]) {
            if (dep[head[a]] < dep[head[b]]) swap(a, b);
            res += bit.range(pos[head[a]], pos[a]); a = par[head[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        return res + bit.range(pos[a], pos[b]);
    };
    cout << "Path sum 3 -> 2: " << path_sum(3, 2) << "\n";
    return 0;
}
