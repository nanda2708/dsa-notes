#include <bits/stdc++.h>
using namespace std;

// Floyd-Warshall All-Pairs Shortest Path | Time: O(V^3) | Space: O(V^2)
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    const long long INF = 1e15;
    int n = 4;
    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    dist[0][1] = 5; dist[1][2] = 3; dist[2][3] = 1; dist[0][3] = 15;
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    cout << "Shortest 0 -> 3: " << dist[0][3] << "\n";
    return 0;
}
