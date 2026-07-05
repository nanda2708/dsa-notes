#include <bits/stdc++.h>
using namespace std;

// Rabin-Karp Rolling Hash | Time: O(N + M) avg | Space: O(1)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s = "abracadabra", pat = "abra";
    int n = (int)s.size(), m = (int)pat.size();
    const long long B = 911382323LL, M = 1000000007LL;
    long long ph = 0, ch = 0, pw = 1;
    for (int i = 0; i < m; ++i) {
        ph = (ph * B + (unsigned char)pat[i]) % M;
        ch = (ch * B + (unsigned char)s[i]) % M;
        if (i) pw = (pw * B) % M;
    }
    for (int i = 0; i + m <= n; ++i) {
        if (ch == ph && s.compare(i, m, pat) == 0) cout << "Match at: " << i << "\n";
        if (i + m < n) {
            ch = (ch - ((unsigned char)s[i] * pw) % M + M) % M;
            ch = (ch * B + (unsigned char)s[i + m]) % M;
        }
    }
    return 0;
}
