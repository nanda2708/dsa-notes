#include <bits/stdc++.h>
using namespace std;

// Aho-Corasick Multi-Pattern Search | Time: O(sum(|P|)*26 + |T|) | Space: O(sum(|P|)*26)
struct AC {
    struct Node { int nxt[26], link = 0, cnt = 0; Node() { fill(nxt, nxt + 26, 0); } };
    vector<Node> tr;
    AC() : tr(1) {}
    void add(const string& p) {
        int u = 0;
        for (char c : p) {
            int idx = c - 'a';
            if (!tr[u].nxt[idx]) { tr[u].nxt[idx] = (int)tr.size(); tr.emplace_back(); }
            u = tr[u].nxt[idx];
        }
        tr[u].cnt++;
    }
    void build() {
        queue<int> q;
        for (int c = 0; c < 26; ++c) if (tr[0].nxt[c]) q.push(tr[0].nxt[c]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int c = 0; c < 26; ++c) {
                int v = tr[u].nxt[c];
                if (v) { tr[v].link = tr[tr[u].link].nxt[c]; tr[v].cnt += tr[tr[v].link].cnt; q.push(v); }
                else tr[u].nxt[c] = tr[tr[u].link].nxt[c];
            }
        }
    }
    int count_matches(const string& t) const {
        int u = 0, ans = 0;
        for (char c : t) { u = tr[u].nxt[c - 'a']; ans += tr[u].cnt; }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    AC ac; ac.add("he"); ac.add("she"); ac.add("his"); ac.add("hers");
    ac.build();
    cout << "Matches in ushers: " << ac.count_matches("ushers") << "\n";
    return 0;
}
