#include <bits/stdc++.h>
using namespace std;

// Lazy Segment Tree (Range Add + Range Sum) | Time: O(log N) | Space: O(4N)
struct LazySeg {
    int n;
    vector<long long> tr, lz;
    LazySeg(const vector<long long>& a) : n((int)a.size()), tr(4 * n), lz(4 * n) { build(a, 1, 0, n - 1); }
    void build(const vector<long long>& a, int u, int l, int r) {
        if (l == r) { tr[u] = a[l]; return; }
        int m = (l + r) / 2;
        build(a, 2 * u, l, m); build(a, 2 * u + 1, m + 1, r);
        tr[u] = tr[2 * u] + tr[2 * u + 1];
    }
    void push(int u, int l, int r) {
        if (!lz[u]) return;
        int m = (l + r) / 2;
        tr[2 * u] += lz[u] * (m - l + 1); lz[2 * u] += lz[u];
        tr[2 * u + 1] += lz[u] * (r - m); lz[2 * u + 1] += lz[u];
        lz[u] = 0;
    }
    void add(int u, int l, int r, int ql, int qr, long long v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { tr[u] += v * (r - l + 1); lz[u] += v; return; }
        push(u, l, r);
        int m = (l + r) / 2;
        add(2 * u, l, m, ql, qr, v); add(2 * u + 1, m + 1, r, ql, qr, v);
        tr[u] = tr[2 * u] + tr[2 * u + 1];
    }
    long long sum(int u, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tr[u];
        push(u, l, r);
        int m = (l + r) / 2;
        return sum(2 * u, l, m, ql, qr) + sum(2 * u + 1, m + 1, r, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    LazySeg st({1, 3, 5, 7, 9});
    st.add(1, 0, 4, 1, 3, 10);
    cout << "Range sum [1, 3]: " << st.sum(1, 0, 4, 1, 3) << "\n";
    return 0;
}
