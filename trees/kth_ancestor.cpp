#include <bits/stdc++.h>
using namespace std;

// K-th Ancestor via Binary Lifting | Time: O(N log N) build, O(log K) query
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 6, LOG = 4;
    vector<int> par = {-1, 0, 1, 2, 2, 4};
    vector<vector<int>> up(LOG, vector<int>(n, -1));
    up[0] = par;
    for (int k = 1; k < LOG; ++k)
        for (int v = 0; v < n; ++v)
            up[k][v] = (up[k - 1][v] == -1) ? -1 : up[k - 1][up[k - 1][v]];
    auto kth = [&](int node, int k) {
        for (int b = 0; b < LOG && node != -1; ++b)
            if ((k >> b) & 1) node = up[b][node];
        return node;
    };
    cout << "2nd ancestor of 4: " << kth(4, 2) << "\n";
    return 0;
}
