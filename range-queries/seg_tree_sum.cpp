#include <bits/stdc++.h>
using namespace std;

// Iterative Segment Tree Range Sum | Time: O(log N) | Space: O(2N)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<long long> a = {1, 2, 3, 4, 5};
    int n = (int)a.size();
    vector<long long> seg(2 * n, 0);
    for (int i = 0; i < n; ++i) seg[n + i] = a[i];
    for (int i = n - 1; i > 0; --i) seg[i] = seg[i << 1] + seg[i << 1 | 1];
    auto add_val = [&](int idx, long long v) {
        for (seg[idx += n] += v; idx > 1; idx >>= 1) seg[idx >> 1] = seg[idx] + seg[idx ^ 1];
    };
    auto range_sum = [&](int l, int r) {
        long long res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += seg[l++];
            if (r & 1) res += seg[--r];
        }
        return res;
    };
    add_val(1, 5);
    cout << "Sum [0, 3]: " << range_sum(0, 3) << "\n";
    return 0;
}
