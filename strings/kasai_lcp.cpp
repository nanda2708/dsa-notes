#include <bits/stdc++.h>
using namespace std;

// Suffix Array + Kasai LCP | Time: O(N log^2 N) SA, O(N) LCP
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s = "banana";
    int n = (int)s.size();
    vector<int> sa(n), rk(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; ++i) rk[i] = (unsigned char)s[i];
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rk[i] != rk[j]) return rk[i] < rk[j];
            return ((i + k < n) ? rk[i + k] : -1) < ((j + k < n) ? rk[j + k] : -1);
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        rk = tmp;
    }
    vector<int> pos(n), lcp(max(0, n - 1), 0);
    for (int i = 0; i < n; ++i) pos[sa[i]] = i;
    for (int i = 0, h = 0; i < n; ++i) {
        if (pos[i] == n - 1) { h = 0; continue; }
        int j = sa[pos[i] + 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
        lcp[pos[i]] = h;
        if (h > 0) --h;
    }
    cout << "Max LCP in banana: " << (lcp.empty() ? 0 : *max_element(lcp.begin(), lcp.end())) << "\n";
    return 0;
}
