#include <bits/stdc++.h>
using namespace std;

// Dijkstra Shortest Path | Time: O((V + E) log V) | Space: O(V + E)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 5;
    vector<vector<pair<int, int>>> adj(n);
    adj[0].push_back({1, 4}); adj[0].push_back({2, 1}); adj[2].push_back({1, 2});
    adj[1].push_back({3, 1}); adj[3].push_back({4, 3});
    const long long INF = 4e18;
    vector<long long> dist(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[0] = 0; pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) { dist[v] = dist[u] + w; pq.push({dist[v], v}); }
        }
    }
    cout << "Shortest 0 -> 4: " << dist[4] << "\n";
    return 0;
}
