# DSA notes

C++17 implementations for placement revision. Each file includes a small example in `main()` so you can compile it and check the result without any dependencies.

| Topic | Implementations | Complexity |
| --- | --- | --- |
| [Strongly connected components](graphs/scc.cpp) | Tarjan and Kosaraju | Both O(V + E) time. Tarjan uses O(V) extra space, excluding output. Kosaraju also stores the reversed graph. |
| [Tree queries](trees/tree_queries.cpp) | Diameter with two BFS passes, kth ancestor, LCA | Diameter takes O(n) time and space. Binary lifting builds in O(n log n) time and space, then answers each query in O(log n). |
| [String matching](strings/pattern_matching.cpp) | Prefix function, KMP, Z-function | Prefix and Z take O(n) time and space. KMP takes O(text + pattern) time and O(pattern) space, excluding matches. |
| [Range sums](range-queries/range_sums.cpp) | Fenwick tree and lazy segment tree | O(log n) per update or query and O(n) space. The segment tree builds in O(n). |

## Details worth remembering

- **SCCs.** In Tarjan, an edge to a vertex already removed from the stack cannot lower the current low-link. Kosaraju processes the reversed graph in decreasing finish order from the original graph. Both examples use recursive DFS, so use an explicit stack if the input can exceed your call stack.
- **Trees.** In a connected, unweighted tree, a vertex farthest from any starting vertex is an endpoint of some diameter. The second BFS measures its distance to the other endpoint. Binary lifting stores ancestors at distances 1, 2, 4, and so on. To find the LCA, first equalize depths, then lift both vertices while their jump targets differ.
- **Strings.** The prefix function describes a proper prefix that also ends at the current position. Z describes how much of the full string's prefix matches starting at each position. In KMP, fall back through the prefix table after a match to keep overlapping matches. For example, `aba` occurs at positions 0 and 2 in `ababa`.
- **Range sums.** Use a Fenwick tree for point additions and prefix sums. Use the lazy tree when updates add to whole ranges. A lazy node's sum already includes its pending delta. Push that delta to the children before a partial update or query.

Graphs and trees use zero-based vertex IDs. The tree examples assume valid, nonempty trees. Range APIs use zero-based half-open intervals `[left, right)` and 64-bit sums.

## Run an example

```sh
g++ -std=c++17 -Wall -Wextra -pedantic trees/tree_queries.cpp -o tree_queries
./tree_queries
```

A successful run exits silently. Leave assertions enabled when running the examples.
