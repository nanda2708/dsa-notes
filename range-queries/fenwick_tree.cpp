#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree (BIT) | Time: O(log N) query/update | Space: O(N)
struct BIT {
    int n; vector<long long> bit;
    BIT(int n) : n(n), bit(n + 1, 0) {}
    void add(int i, long long v) { for (++i; i <= n; i += i & -i) bit[i] += v; }
    long long sum(int i) const { long long s = 0; for (++i; i > 0; i -= i & -i) s += bit[i]; return s; }
    long long range(int l, int r) const { return l > r ? 0 : sum(r) - (l ? sum(l - 1) : 0); }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<int> a = {2, 1, 4, 3, 5};
    BIT ft((int)a.size());
    for (int i = 0; i < (int)a.size(); ++i) ft.add(i, a[i]);
    ft.add(2, 3);
    cout << "Sum [1, 4]: " << ft.range(1, 4) << "\n";
    return 0;
}
