#include <bits/stdc++.h>
using namespace std;

// Trie Prefix Tree | Time: O(L) | Space: O(total chars)
struct Trie {
    struct Node {
        int nxt[26], pref = 0;
        Node() { fill(nxt, nxt + 26, -1); }
    };
    vector<Node> tr;
    Trie() : tr(1) {}
    void insert(const string& s) {
        int u = 0;
        tr[u].pref++;
        for (char c : s) {
            int idx = c - 'a';
            if (tr[u].nxt[idx] == -1) {
                tr[u].nxt[idx] = (int)tr.size();
                tr.emplace_back();
            }
            u = tr[u].nxt[idx];
            tr[u].pref++;
        }
    }
    int prefix_count(const string& p) const {
        int u = 0;
        for (char c : p) {
            int idx = c - 'a';
            if (tr[u].nxt[idx] == -1) return 0;
            u = tr[u].nxt[idx];
        }
        return tr[u].pref;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Trie t;
    t.insert("apple"); t.insert("app"); t.insert("apply");
    cout << "Prefix app: " << t.prefix_count("app") << "\n";
    return 0;
}
