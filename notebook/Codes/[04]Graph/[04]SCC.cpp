typedef long long LL;
const LL N = 1e6 + 7;

bool vis[N];
int root[N];
vector<int> adj[N], adjr[N], adj_scc[N];
vector<int> order, component, roots;
// tp = 0 ,finding topo order, tp = 1 , reverse edge traversal

void dfs(int u, int tp = 0) {
  vis[u] = true;
  if (tp) component.push_back(u);
  auto& ad = (tp ? adjr : adj);
  for (int v : ad[u])
    if (!vis[v]) dfs(v, tp);
  if (!tp) order.push_back(u);
}

int main() {
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }
  memset(vis, 0, sizeof vis);
  reverse(order.begin(), order.end());
  for (int i : order) {
    if (!vis[i]) {
      dfs(i, 1);
      int rt = component[0];
      for (auto j : component)
        root[j] = rt;
      roots.push_back(rt);
      component.clear();
    }
  }

  for (int u = 1; u <= n; u++)
    for (auto v : adj[u]) {
      int rtu = root[u],
          rtv = root[v];
      if (rtu != rtv)
        adj_scc[rtu].push_back(rtv);
    }
}
