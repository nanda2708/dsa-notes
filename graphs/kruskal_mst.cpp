#include <bits/stdc++.h>
using namespace std;

// Kruskal MST + DSU | Time: O(E log E) | Space: O(V)
struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b]; return true;
    }
};
struct Edge { int u, v, w; };
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<Edge> es = {{0,1,10},{0,2,6},{0,3,5},{1,3,15},{2,3,4}};
    sort(es.begin(), es.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    DSU dsu(4);
    long long cost = 0;
    for (auto& e : es) if (dsu.unite(e.u, e.v)) cost += e.w;
    cout << "MST cost: " << cost << "\n";
    return 0;
}
