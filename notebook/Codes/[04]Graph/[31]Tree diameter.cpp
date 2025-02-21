namespace Diameter {
    using Tree = vector<vector<int>>;
    vector<int> bfs(const Tree& g, int root) {
        queue<int> q;
        q.push(root);
        vector<int> lvl(g.size());
        lvl[root] = 1;
        while (q.size()) {
            int u = q.front(); q.pop();
            for (auto v: g[u]) if (not lvl[v]) {
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
        return lvl;
    }
    bool dfs(vector<int>& ans, const Tree& g, int u, int d, int p = -1) {
        ans.push_back(u);
        if (u == d) return true;
        for (auto v: g[u]) if (v xor p)
            if (dfs(ans, g, v, d, u))
                return true;
        ans.pop_back();
        return false;
    }
    vector<int> find_diameter(const Tree &g) {
        auto d = bfs(g, 1);
        int u = max_element(all(d)) - d.begin();
        d = bfs(g, u);
        int v = max_element(all(d)) - d.begin();
        vector<int> ret;
        dfs(ret, g, u, v);
        return ret;
    }
    vector<int> find_center(const Tree& g) {
        auto v = find_diameter(g);
        int l = 0, r = v.size() - 1;
        for (; r-l+1 > 2; l++, r--);
        if (l == r) return {v[l]};
        return {v[l], v[r]};
    }
}
