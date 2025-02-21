namespace centroid {
	const int N = 2e5;
	int sz[N+1];
	bitset<N> vis;
	vector<int> adj[N+1];
	void dfs_size(int u = 1, int p = 0) {
		sz[u] = 1;
		for (auto v : adj[u])
			if (v != p) {
				dfs_size(v, u);
				sz[u] += sz[v];
			}
	}
	int find_centroid(int u, int p) {
		int total = sz[u];
		for (auto v : adj[u])
			if (v != p and not vis[v] and 2 * sz[v] > total) {
				sz[u] = total - sz[v];
				sz[v] = total;
				return find_centroid(v, u);
			}
		return u;
	}
	int query(int u) {
		int ans = 1e6;
		for (int i = u; i; i = par[i])
			ans = min(ans, minD[i] + lca::dist(i, u));
		return ans;
	}
	void update(int u) {
		for (int i = u; i; i = par[i])
			minD[i] = min(minD[i], lca::dist(i, u));
	}
	int decompose(int u, int p) {
		u = find_centroid(u, p);
		vis[u] = 1;
		for (auto v : adj[u])
			if (not vis[v])
				par[decompose(v, u)] = u;
		return u;
	}
}
