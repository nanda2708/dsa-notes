#include <bits/stdc++.h>
using namespace std;

// Sparse Table RMQ | Time: O(N log N) build, O(1) query | Space: O(N log N)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<int> a = {7, 2, 3, 0, 5, 10, 3, 12};
    int n = (int)a.size(), K = __lg(n) + 1;
    vector<vector<int>> st(K, vector<int>(n));
    st[0] = a;
    for (int k = 1; k < K; ++k)
        for (int i = 0; i + (1 << k) <= n; ++i)
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    auto rmq = [&](int l, int r) { int j = __lg(r - l + 1); return min(st[j][l], st[j][r - (1 << j) + 1]); };
    cout << "Min [0, 4]: " << rmq(0, 4) << ", [4, 7]: " << rmq(4, 7) << "\n";
    return 0;
}
