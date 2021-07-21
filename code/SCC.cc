vi val, comp, z, cont;
int Time, ncomps;
// A function that will be called with the indicies of all elements
// in each component as the parameter once per component after running scc.
void f(vi node_inds) {};
int dfs(int j, vector<vi>& g) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for (auto e : g[j]) if (comp[e] < 0)
            low = min(low, val[e] ?: dfs(e,g));

    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
void scc(vector<vi>& g) {
    int n = g.size();
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i,0,n) if (comp[i] < 0) dfs(i, g);
}
