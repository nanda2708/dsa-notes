#include <bits/stdc++.h>
using namespace std;

// Merge Sort Tree: Count Elements > k in [l, r] | Time: O(N log N) build, O(log^3 N) query
struct MST {
    int n; vector<vector<int>> tr;
    MST(const vector<int>& a) : n((int)a.size()), tr(4 * n) { if (n) build(a, 1, 0, n - 1); }
    void build(const vector<int>& a, int u, int l, int r) {
        if (l == r) { tr[u] = {a[l]}; return; }
        int m = (l + r) / 2;
        build(a, 2 * u, l, m); build(a, 2 * u + 1, m + 1, r);
        auto& cur = tr[u]; const auto& L = tr[2 * u]; const auto& R = tr[2 * u + 1];
        cur.resize(L.size() + R.size());
        merge(L.begin(), L.end(), R.begin(), R.end(), cur.begin());
    }
    int gt(int u, int l, int r, int ql, int qr, int k) const {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return (int)(tr[u].end() - upper_bound(tr[u].begin(), tr[u].end(), k));
        int m = (l + r) / 2;
        return gt(2 * u, l, m, ql, qr, k) + gt(2 * u + 1, m + 1, r, ql, qr, k);
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<int> a = {10, 2, 15, 8, 20, 5};
    MST mst(a);
    cout << "Count > 8: " << mst.gt(1, 0, (int)a.size() - 1, 0, 5, 8) << "\n";
    return 0;
}
