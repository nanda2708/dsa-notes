#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

using Graph = std::vector<std::vector<int>>;

Graph tarjan(const Graph& graph) {
    int next = 0;
    std::vector<int> order(graph.size(), -1), low(graph.size()), stack;
    std::vector<bool> active(graph.size());
    Graph components;
    std::function<void(int)> dfs = [&](int u) {
        order[u] = low[u] = next++;
        active[u] = true;
        stack.push_back(u);
        for (int v : graph[u]) {
            if (order[v] == -1) {
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (active[v]) {
                low[u] = std::min(low[u], order[v]);
            }
        }
        if (low[u] != order[u]) return;
        auto& component = components.emplace_back();
        while (true) {
            int v = stack.back();
            stack.pop_back();
            active[v] = false;
            component.push_back(v);
            if (v == u) break;
        }
    };
    for (int u = 0; u < static_cast<int>(graph.size()); ++u)
        if (order[u] == -1) dfs(u);
    return components;
}

Graph kosaraju(const Graph& graph) {
    Graph reverse(graph.size()), components;
    std::vector<bool> seen(graph.size());
    std::vector<int> order;
    for (int u = 0; u < static_cast<int>(graph.size()); ++u)
        for (int v : graph[u]) reverse[v].push_back(u);

    std::function<void(int)> finish = [&](int u) {
        seen[u] = true;
        for (int v : graph[u]) if (!seen[v]) finish(v);
        order.push_back(u);
    };
    for (int u = 0; u < static_cast<int>(graph.size()); ++u)
        if (!seen[u]) finish(u);

    std::fill(seen.begin(), seen.end(), false);
    std::function<void(int)> collect = [&](int u) {
        seen[u] = true;
        components.back().push_back(u);
        for (int v : reverse[u]) if (!seen[v]) collect(v);
    };
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        if (seen[*it]) continue;
        components.emplace_back();
        collect(*it);
    }
    return components;
}

int main() {
    const Graph graph{{1}, {0, 2}, {3}, {2}, {4, 0}, {}};
    const Graph expected{{0, 1}, {2, 3}, {4}, {5}};
    for (auto components : {tarjan(graph), kosaraju(graph)}) {
        for (auto& group : components) std::sort(group.begin(), group.end());
        std::sort(components.begin(), components.end());
        assert(components == expected);
    }
}
