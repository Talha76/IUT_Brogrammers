/*
 * - Use add_edge(u, v, w) to add edge
 * - At first implement LCA
 * - Call init_lca, dfs
 * - Call get_virtual_tree(nodes) -> vector<int>: nodes in virtual tree
 */
struct virtual_tree {
    vector<vector<PII>> g, vt;
    vector<int> in, val, out;
    LCA lca;
    int t;
    virtual_tree() {}
    virtual_tree(int n) : g(n+1), vt(n+1), in(n+1), val(n+1), out(n+1), t(0) {}
    void add_edge(int u, int v, int w = 1) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    void init_lca(int root) {
        vector<vector<int>> _g(g.size());
        for (int u = 0; u < g.size(); u++)
            for (auto [v, w]: g[u])
                _g[u].push_back(v);
        lca = LCA(_g, root, root);
    }
    void dfs(int u, int p = -1, int d = 0) {
        in[u] = ++t;
        val[u] = d;
        for (auto [v, w]: g[u])
            if (v xor p)
                dfs(v, u, d+w);
        out[u] = t;
    }
    bool is_anc(int u, int p) {
        return in[p] <= in[u] and out[u] <= out[p];
    }
    void clear(vector<int> nodes) {
        for (auto e: nodes) 
            vt[e].clear();
    }
    vector<int> get_virtual_tree(vector<int> v) {
        sort(all(v), [&](int a, int b) { return in[a] < in[b]; });
        int n = v.size();
        for (int i = 1; i < n; i++)
            v.push_back(lca.lca(v[i], v[i-1]));
        sort(all(v), [&](int a, int b) { return in[a] < in[b]; });
        v.erase(unique(all(v)), v.end());
        stack<int> s;
        s.push(v[0]);
        for (int i = 1; i < v.size(); i++) {
            while (not is_anc(v[i], s.top())) s.pop();
            vt[s.top()].emplace_back(v[i], val[v[i]] - val[s.top()]);
            vt[v[i]].emplace_back(s.top(), val[v[i]] - val[s.top()]);
            s.push(v[i]);
        }
        return v;
    }
};
