#include <bits/stdc++.h>
using namespace std;

// Polynomial Rolling Hash Substring Match | Time: O(N) build, O(1) query | Space: O(N)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s = "abacaba";
    int n = (int)s.size();
    const long long B = 131LL, M = 1000000007LL;
    vector<long long> h(n + 1, 0), pw(n + 1, 1);
    for (int i = 0; i < n; ++i) {
        h[i + 1] = (h[i] * B + (unsigned char)s[i]) % M;
        pw[i + 1] = (pw[i] * B) % M;
    }
    auto sub_hash = [&](int l, int len) {
        return (h[l + len] - (h[l] * pw[len]) % M + M) % M;
    };
    cout << "Prefix(3) == Suffix(3): " << (sub_hash(0, 3) == sub_hash(4, 3) ? "Yes" : "No") << "\n";
    return 0;
}
