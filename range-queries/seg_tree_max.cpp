#include <bits/stdc++.h>
using namespace std;

// Iterative Segment Tree (Point Update + Range Max) | Time: O(log N) | Space: O(2N)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<long long> a = {4, 2, 9, 1, 7, 6};
    int n = (int)a.size();
    const long long NEG_INF = -4e18;
    vector<long long> seg(2 * n, NEG_INF);
    for (int i = 0; i < n; ++i) seg[n + i] = a[i];
    for (int i = n - 1; i > 0; --i) seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
    auto update = [&](int idx, long long val) {
        for (seg[idx += n] = val; idx > 1; idx >>= 1) seg[idx >> 1] = max(seg[idx], seg[idx ^ 1]);
    };
    auto query_max = [&](int l, int r) {
        long long res = NEG_INF;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, seg[l++]);
            if (r & 1) res = max(res, seg[--r]);
        }
        return res;
    };
    update(3, 15);
    cout << "Max [0, 3]: " << query_max(0, 3) << "\n";
    return 0;
}
