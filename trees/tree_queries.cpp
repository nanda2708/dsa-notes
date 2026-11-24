#include <cassert>
#include <queue>
#include <utility>
#include <vector>

using Tree = std::vector<std::vector<int>>;

// A nonempty, connected, unweighted tree. Length is in edges.
int diameter(const Tree& tree) {
    auto farthest = [&](int start) {
        std::vector<int> distance(tree.size(), -1);
        std::queue<int> queue;
        distance[start] = 0;
        queue.push(start);
        int best = start;
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            if (distance[u] > distance[best]) best = u;
            for (int v : tree[u]) {
                if (distance[v] != -1) continue;
                distance[v] = distance[u] + 1;
                queue.push(v);
            }
        }
        return std::pair{best, distance[best]};
    };
    return farthest(farthest(0).first).second;
}

class BinaryLifting {
public:
    BinaryLifting(const Tree& tree, int root) : depth(tree.size(), -1) {
        int levels = 1;
        while ((1LL << levels) < static_cast<long long>(tree.size())) ++levels;
        up.assign(levels, std::vector<int>(tree.size(), root));
        std::queue<int> queue;
        depth[root] = 0;
        queue.push(root);
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            for (int v : tree[u]) {
                if (depth[v] != -1) continue;
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                queue.push(v);
            }
        }
        for (int j = 1; j < levels; ++j)
            for (int u = 0; u < static_cast<int>(tree.size()); ++u)
                up[j][u] = up[j - 1][up[j - 1][u]];
    }

    int ancestor(int u, int steps) const {
        assert(steps >= 0);
        if (steps > depth[u]) return -1;
        for (int j = 0; steps != 0; ++j, steps >>= 1)
            if (steps & 1) u = up[j][u];
        return u;
    }

    int lca(int u, int v) const {
        if (depth[u] < depth[v]) std::swap(u, v);
        u = ancestor(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int j = static_cast<int>(up.size()) - 1; j >= 0; --j) {
            if (up[j][u] == up[j][v]) continue;
            u = up[j][u];
            v = up[j][v];
        }
        return up[0][u];
    }

private:
    std::vector<int> depth;
    std::vector<std::vector<int>> up;
};

int main() {
    const Tree tree{{1, 2}, {0, 3, 4}, {0}, {1}, {1, 5}, {4}};
    BinaryLifting lift(tree, 0);
    assert(diameter(tree) == 4);
    assert(diameter(Tree(1)) == 0);
    assert(lift.ancestor(5, 2) == 1);
    assert(lift.ancestor(5, 4) == -1);
    assert(lift.lca(3, 5) == 1);
    assert(lift.lca(0, 5) == 0);
}
