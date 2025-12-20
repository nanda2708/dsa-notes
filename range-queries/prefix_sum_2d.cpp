#include <bits/stdc++.h>
using namespace std;

// 2D Prefix Sum Submatrix Query | Time: O(R*C) build, O(1) query | Space: O(R*C)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int r = (int)a.size(), c = (int)a[0].size();
    vector<vector<long long>> ps(r + 1, vector<long long>(c + 1, 0));
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            ps[i][j] = a[i - 1][j - 1] + ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
    cout << "Submatrix sum: " << (ps[3][3] - ps[0][3] - ps[3][1] + ps[0][1]) << "\n";
    return 0;
}
