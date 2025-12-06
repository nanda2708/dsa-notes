#include <bits/stdc++.h>
using namespace std;

// Unweighted Shortest Path via BFS | Time: O(V + E) | Space: O(V)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 5;
    vector<vector<int>> adj(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(0, 2); edge(1, 3); edge(2, 4);
    vector<int> dist(n, -1); queue<int> q;
    dist[0] = 0; q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (dist[v] == -1) { dist[v] = dist[u] + 1; q.push(v); }
    }
    cout << "Dist 0 -> 4: " << dist[4] << "\n";
    return 0;
}
