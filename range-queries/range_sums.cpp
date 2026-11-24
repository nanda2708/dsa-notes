#include <cassert>
#include <vector>

class Fenwick {
public:
    explicit Fenwick(int size) : bit(size + 1) {}

    void add(int index, long long delta) {
        assert(index >= 0 && index < static_cast<int>(bit.size()) - 1);
        for (int i = index + 1; i < static_cast<int>(bit.size()); i += i & -i)
            bit[i] += delta;
    }

    long long prefix(int end) const {
        assert(end >= 0 && end < static_cast<int>(bit.size()));
        long long result = 0;
        for (int i = end; i > 0; i -= i & -i) result += bit[i];
        return result;
    }

    long long sum(int left, int right) const {
        assert(left <= right);
        return prefix(right) - prefix(left);
    }

private:
    std::vector<long long> bit;
};

class LazySegmentTree {
public:
    explicit LazySegmentTree(const std::vector<long long>& values)
        : n(static_cast<int>(values.size())), total(4 * values.size()),
          pending(4 * values.size()) {
        if (n != 0) build(1, 0, n, values);
    }

    void add(int left, int right, long long delta) {
        assert(0 <= left && left <= right && right <= n);
        if (left != right) update(1, 0, n, left, right, delta);
    }

    long long sum(int left, int right) {
        assert(0 <= left && left <= right && right <= n);
        return left == right ? 0 : query(1, 0, n, left, right);
    }

private:
    int n;
    std::vector<long long> total, pending;

    void build(int node, int lo, int hi, const std::vector<long long>& values) {
        if (hi - lo == 1) {
            total[node] = values[lo];
            return;
        }
        int mid = lo + (hi - lo) / 2;
        build(2 * node, lo, mid, values);
        build(2 * node + 1, mid, hi, values);
        pull(node);
    }

    void pull(int node) { total[node] = total[2 * node] + total[2 * node + 1]; }

    void apply(int node, int length, long long delta) {
        total[node] += length * delta;
        pending[node] += delta;
    }

    void push(int node, int lo, int mid, int hi) {
        if (pending[node] == 0) return;
        apply(2 * node, mid - lo, pending[node]);
        apply(2 * node + 1, hi - mid, pending[node]);
        pending[node] = 0;
    }

    void update(int node, int lo, int hi, int left, int right, long long delta) {
        if (right <= lo || hi <= left) return;
        if (left <= lo && hi <= right) {
            apply(node, hi - lo, delta);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        push(node, lo, mid, hi);
        update(2 * node, lo, mid, left, right, delta);
        update(2 * node + 1, mid, hi, left, right, delta);
        pull(node);
    }

    long long query(int node, int lo, int hi, int left, int right) {
        if (right <= lo || hi <= left) return 0;
        if (left <= lo && hi <= right) return total[node];
        int mid = lo + (hi - lo) / 2;
        push(node, lo, mid, hi);
        return query(2 * node, lo, mid, left, right) +
               query(2 * node + 1, mid, hi, left, right);
    }
};

int main() {
    Fenwick bit(4);
    bit.add(0, 2);
    bit.add(2, 7);
    bit.add(2, -3);
    assert(bit.prefix(4) == 6);
    assert(bit.sum(1, 3) == 4);
    assert(bit.sum(2, 2) == 0);

    LazySegmentTree tree({1, 2, 3, 4});
    tree.add(1, 4, 5);
    tree.add(0, 2, -2);
    assert(tree.sum(0, 4) == 21);
    assert(tree.sum(1, 3) == 13);
    assert(tree.sum(3, 4) == 9);
    assert(tree.sum(0, 0) == 0);
    LazySegmentTree empty({});
    assert(empty.sum(0, 0) == 0);
}
