#include <bits/stdc++.h>
using namespace std;

// Manacher Longest Palindromic Substring | Time: O(N) | Space: O(N)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s = "babad", t = "#";
    for (char c : s) { t.push_back(c); t.push_back(
