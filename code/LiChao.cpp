// Li-Chao Tree. Store a family of functions with domain a subset of R
// where no two functions intersect
// more than once. Support querying for the max of all functions in the tree
// in O(log(n)) with O(log(n)) insertion
struct LiChao {
    typedef int ftype;
    typedef pair<int, int> params;
    int maxn;

    vector<params> best_params;

    LiChao(int maxN) {
        maxn = maxN;
        best_params = vector<params>(maxn * 4);
    }

    // The function you add to the tree. It is a family of functions
    // parameterized by a
    // Any two functions f(a, -), f(b, -) must intersect at most once,
    // else the tree will not work.
    ftype f(params a, ftype x) {
        return a.first * x + a.second;
    }

    // Add the function parameterized by nw to the tree
    void add_fn(params nw, int v, int l, int r) {
        int m = (l + r) / 2;
        bool lef = f(nw, l) < f(best_params[v], l);
        bool mid = f(nw, m) < f(best_params[v], m);
        if (mid) {
            swap(best_params[v], nw);
        }
        if (r - l == 1) {
            return;
        } else if (lef != mid) {
            add_fn(nw, 2 * v, l, m);
        } else {
            add_fn(nw, 2 * v + 1, m, r);
        }
    }

    void add_fn(params nw) {
        return add_fn(nw, 1, 0, maxn);
    }

    // Compute the maximum valued function over all x
    int get(int x, int v, int l, int r) {
        int m = (l + r) / 2;
        if (r - l == 1) {
            return f(best_params[v], x);
        } else if (x < m) {
            return min(f(best_params[v], x), get(x, 2 * v, l, m));
        } else {
            return min(f(best_params[v], x), get(x, 2 * v + 1, m, r));
        }
    }

    int get(int x) {
        return get(x, 1, 0, maxn);
    }
};

