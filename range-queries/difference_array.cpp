#include <bits/stdc++.h>
using namespace std;

// Difference Array Range Increment | Time: O(Q + N) | Space: O(N)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n = 5;
    vector<long long> diff(n + 1, 0);
    auto add_range = [&](int l, int r, long long val) {
        diff[l] += val;
        if (r + 1 < n) diff[r + 1] -= val;
    };
    add_range(1, 3, 5); add_range(2, 4, 2);
    long long cur = 0;
    for (int i = 0; i < n; ++i) { cur += diff[i]; cout << cur << (i + 1 == n ? "\n" : " "); }
    return 0;
}
