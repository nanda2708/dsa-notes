#include <bits/stdc++.h>
using namespace std;

// Longest Common Prefix of String Array | Time: O(total chars) | Space: O(1)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<string> words = {"flower", "flow", "flight"};
    string pref = words[0];
    for (size_t i = 1; i < words.size(); ++i) {
        while (words[i].find(pref) != 0) {
            pref.pop_back();
            if (pref.empty()) break;
        }
    }
    cout << "LCP: " << pref << "\n";
    return 0;
}
