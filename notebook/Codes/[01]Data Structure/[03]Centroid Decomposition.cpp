// problem: Xenia and Tree
// Centroid Tree Implementation
#define lg(n) (31 - __builtin_clz(n))

const int N = 1e5 + 1;
const int K = lg(N) + 1;

int n;
vector<int> adj[N];
int anc[N][K], lvl[N], par[N], sz[N], vis[N];
int minD[N];

namespace CD {
  // Call dfs at the very outset
  void dfs(int u = 1, int p = 0) {
    sz[u] = 1;
    for (auto v : adj[u])
      if (v != p) {
        dfs_size(v, u);
        sz[u] += sz[v];
      }
  }

  int findCentroid(int u, int p) {
    int total = sz[u];
    for (auto v : adj[u])
      if (v != p and not vis[v] and 2 * sz[v] > total) {
        sz[u] = total - sz[v];
        sz[v] = total;
        return findCentroid(v, u);
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
    u = findCentroid(u, p);
    vis[u] = 1;
    for (auto v : adj[u])
      if (not vis[v])
        par[decompose(v, u)] = u;
    return u;
  }
}

int main() {
  cin.tie(NULL)->sync_with_stdio(false);
  fill(all(minD), 1e9);

  int m;
  cin >> n >> m;
  for (int u, v, i = 1; i < n; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  lca::init();
  CD::dfs();
  CD::decompose(1, 0);

  CD::update(1);
  int t, v;
  while (m--) {
    cin >> t >> v;
    if (t == 1) CD::update(v);
    else cout << CD::query(v) << '\n';
  }

  return 0;
}
