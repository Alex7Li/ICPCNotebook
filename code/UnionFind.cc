/**
 * Description: Disjoint-set data structure.
 * Time: $O(alpha(N))$
 */
struct UF {
    // E is parent set number if positive, and the size if negative.
    // If negative, it's the root of a set.
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    int find2(int x) { // Dennis's faster union find
        while (e[x] >= 0) {e[x] = e[e[x]]; x = e[x]}
        return x;
    }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};