#include <bits/stdc++.h>
using namespace std;

// Dinic Maximum Flow | Time: O(V^2 * E) | Space: O(V + E)
struct Dinic {
    struct Edge { int to, rev; long long cap; };
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;
    Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}
    void add_edge(int u, int v, long long cap) {
        adj[u].push_back({v, (int)adj[v].size(), cap});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& e : adj[u])
                if (e.cap > 0 && level[e.to] == -1) { level[e.to] = level[u] + 1; q.push(e.to); }
        }
        return level[t] != -1;
    }
    long long dfs(int u, int t, long long pushed) {
        if (!pushed || u == t) return pushed;
        for (int& cid = ptr[u]; cid < (int)adj[u].size(); ++cid) {
            auto& e = adj[u][cid];
            if (level[e.to] != level[u] + 1 || !e.cap) continue;
            long long tr = dfs(e.to, t, min(pushed, e.cap));
            if (!tr) continue;
            e.cap -= tr; adj[e.to][e.rev].cap += tr;
            return tr;
        }
        return 0;
    }
    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long p = dfs(s, t, 4e18)) flow += p;
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    Dinic g(4);
    g.add_edge(0, 1, 10); g.add_edge(0, 2, 10); g.add_edge(1, 3, 4); g.add_edge(2, 3, 8);
    cout << "Max flow: " << g.max_flow(0, 3) << "\n";
    return 0;
}
