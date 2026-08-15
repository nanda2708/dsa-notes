#include <bits/stdc++.h>
using namespace std;

// Linear XOR Basis | Time: O(B) | Space: O(B)
struct Basis {
    int b[30] = {};
    void insert(int x) {
        for (int i = 29; i >= 0; --i) {
            if (!((x >> i) & 1)) continue;
            if (!b[i]) { b[i] = x; return; }
            x ^= b[i];
        }
    }
    int max_xor() const {
        int res = 0;
        for (int i = 29; i >= 0; --i) if ((res ^ b[i]) > res) res ^= b[i];
        return res;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Basis xb;
    for (int x : {3, 10, 5}) xb.insert(x);
    cout << "Max XOR: " << xb.max_xor() << "\n";
    return 0;
}
