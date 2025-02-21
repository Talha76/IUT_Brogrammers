struct LCA {
    int n;
    vector<int> lvl, par, jmp;
    LCA(vector<vector<int>> const& g, int u, int p) : n(g.size()), lvl(n, -1), par(n, -1), jmp(n, p) {
        lvl[u] = 0, par[u] = p;
        queue<int> q;
        for (q.push(u); q.size(); q.pop()) {
            int u = q.front();
            for (int v: g[u]) if (lvl[v] < 0) {
                q.push(v);
                lvl[v] = lvl[u] + 1, par[v] = u;
                if (lvl[jmp[u]] << 1 == lvl[u] + lvl[jmp[jmp[u]]]) jmp[v] = jmp[jmp[u]];
                else jmp[v] = u;
            }
        }
    }
    int getAnc(int u, int d) {
        d = max(0, lvl[u] - d);
        while (lvl[u] > d) {
            if (lvl[jmp[u]] < d) u = par[u];
            else u = jmp[u];
        }
        return u;
    }
    int lca(int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        u = getAnc(u, lvl[u] - lvl[v]);
        while (u != v) {
            if (jmp[u] == jmp[v]) u = par[u], v = par[v];
            else u = jmp[u], v = jmp[v];
        }
        return u;
    }
    int dist(int u, int v) { return lvl[u] + lvl[v] - 2*lvl[lca(u, v)]; }
};
