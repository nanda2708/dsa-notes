#include <bits/stdc++.h>
using namespace std;

// Z-Algorithm Pattern Search | Time: O(N + M) | Space: O(N + M)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string text = "ababcababdabab", pat = "abab", s = pat + "#" + text;
    int n = (int)s.size(), m = (int)pat.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) { l = i; r = i + z[i] - 1; }
        if (i > m && z[i] == m) cout << "Match at: " << i - m - 1 << "\n";
    }
    return 0;
}
