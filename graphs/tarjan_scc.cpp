#include <bits/stdc++.h>
using namespace std;

// Tarjan Strongly Connected Components | Time: O(V + E) | Space: O(V)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 5, timer = 0, sccs = 0;
    vector<vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(2); adj[2].push_back(0);
    adj[2].push_back(3); adj[3].push_back(4);
    vector<int> tin(n, 0), low(n, 0);
    vector<bool> on_st(n, false);
    stack<int> st;
    auto dfs = [&](auto& self, int u) -> void {
        tin[u] = low[u] = ++timer;
        st.push(u); on_st[u] = true;
        for (int v : adj[u]) {
            if (!tin[v]) { self(self, v); low[u] = min(low[u], low[v]); }
            else if (on_st[v]) low[u] = min(low[u], tin[v]);
        }
        if (low[u] == tin[u]) {
            ++sccs;
            while (true) {
                int x = st.top(); st.pop(); on_st[x] = false;
                if (x == u) break;
            }
        }
    };
    for (int i = 0; i < n; ++i) if (!tin[i]) dfs(dfs, i);
    cout << "SCC count: " << sccs << "\n";
    return 0;
}
