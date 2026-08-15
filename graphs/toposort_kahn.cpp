#include <bits/stdc++.h>
using namespace std;

// Kahn Topological Sort | Time: O(V + E) | Space: O(V + E)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 6;
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0);
    auto edge = [&](int u, int v) { adj[u].push_back(v); indeg[v]++; };
    edge(5, 2); edge(5, 0); edge(4, 0); edge(4, 1); edge(2, 3); edge(3, 1);
    queue<int> q;
    for (int i = 0; i < n; ++i) if (!indeg[i]) q.push(i);
    vector<int> ord;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ord.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    cout << "Topo count: " << ord.size() << "\n";
    return 0;
}
