#include <bits/stdc++.h>
using namespace std;

// Tree Diameter via Two BFS Passes | Time: O(N) | Space: O(N)
pair<int, int> farthest(int s, const vector<vector<int>>& adj) {
    int n = (int)adj.size();
    vector<int> d(n, -1); queue<int> q;
    d[s] = 0; q.push(s);
    int best = s;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (d[u] > d[best]) best = u;
        for (int v : adj[u]) if (d[v] == -1) { d[v] = d[u] + 1; q.push(v); }
    }
    return {best, d[best]};
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 6;
    vector<vector<int>> adj(n);
    auto edge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    edge(0, 1); edge(1, 2); edge(2, 3); edge(1, 4); edge(4, 5);
    auto [u, _] = farthest(0, adj);
    auto [v, diam] = farthest(u, adj);
    cout << "Diameter: " << diam << " (" << u << " to " << v << ")\n";
    return 0;
}
