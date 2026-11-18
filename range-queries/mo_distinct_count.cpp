#include <bits/stdc++.h>
using namespace std;

// Mo Algorithm for Offline Distinct Count | Time: O((N + Q) sqrt(N))
struct Query { int l, r, id; };
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<int> a = {1, 1, 2, 1, 3}, freq(10, 0), ans(2);
    vector<Query> qs = {{0, 4, 0}, {1, 3, 1}};
    int blk = max(1, (int)sqrt(a.size())), cl = 0, cr = -1, dist = 0;
    sort(qs.begin(), qs.end(), [&](Query x, Query y) {
        return (x.l / blk != y.l / blk) ? (x.l < y.l) : (x.r < y.r);
    });
    auto add = [&](int i) { if (++freq[a[i]] == 1) ++dist; };
    auto rem = [&](int i) { if (--freq[a[i]] == 0) --dist; };
    for (auto q : qs) {
        while (cl > q.l) add(--cl);
        while (cr < q.r) add(++cr);
        while (cl < q.l) rem(cl++);
        while (cr > q.r) rem(cr--);
        ans[q.id] = dist;
    }
    cout << "Distinct [0,4]: " << ans[0] << ", [1,3]: " << ans[1] << "\n";
    return 0;
}
