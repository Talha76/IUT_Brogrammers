#define lg(n) (31 - __builtin_clz(n))

const int N = 1e5 + 1;
const int K = lg(N) + 1;

vector<int> adj[N];
int anc[N][K], lvl[N];

namespace lca {
  void init(int u = 1, int p = 0, int d = 0) {
    lvl[u] = d;
    anc[u][0] = p;
    for (int i = 1; i < K; i++)
      anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (auto v : adj[u])
      if (v != p)
        init(v, u, d + 1);
  }

  int getAnc(int u, int k) {
    for (int i = 0; u and i < K; i++)
      if ((k >> i) & 1)
        u = anc[u][i];
    return u;
  }

  int lca(int u, int v) {
    if (lvl[u] < lvl[v]) swap(u, v);
    u = getAnc(u, lvl[u] - lvl[v]);
    if (u == v) return u;
    for (int i = K - 1; ~i; i--)
      if (anc[u][i] != anc[v][i])
        u = anc[u][i], v = anc[v][i];
    return anc[u][0];
  }

  int dist(int u, int v) {
    return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];
  }
}

struct euler_tour {
  int time = 0;
  tree &T;
  int n;
  vector<int> start, finish, level, par;
  euler_tour(tree &T, int root = 0)
      : T(T), n(T.n), start(n), finish(n), level(n), par(n) {
    time = 0;
    call(root);
  }
  void call(int node, int p = -1) {
    if (p != -1) level[node] = level[p] + 1;
    start[node] = time++;
    for (int e : T[node])
      if (e != p) call(e, node);
    par[node] = p;
    finish[node] = time++;
  }
  bool isAncestor(int node, int par) {
    return start[par] <= start[node] and finish[par] >= finish[node];
  }
  int subtreeSize(int node) { return finish[node] - start[node] + 1 >> 1; }
};

tree virtual_tree(vector<int> &nodes, lca_table &table, euler_tour &tour) {
  sort(nodes.begin(), nodes.end(),
       [&](int x, int y) { return tour.start[x] < tour.start[y]; });
  int n = nodes.size();
  for (int i = 0; i + 1 < n; i++)
    nodes.push_back(table.lca(nodes[i], nodes[i + 1]));
  sort(nodes.begin(), nodes.end());
  nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
  sort(nodes.begin(), nodes.end(),
       [&](int x, int y) { return tour.start[x] < tour.start[y]; });
  n = nodes.size();
  stack<int> st;
  st.push(0);
  tree ans(n);
  for (int i = 1; i < n; i++) {
    while (!tour.isAncestor(nodes[i], nodes[st.top()])) st.pop();
    ans.addEdge(st.top(), i);
    st.push(i);
  }
  return ans;
}

set<int> getCenters(tree &T) {
  int n = T.n;
  vector<int> deg(n), q;
  set<int> s;
  for (int i = 0; i < n; i++) {
    deg[i] = T[i].size();
    if (deg[i] == 1) q.push_back(i);
    s.insert(i);
  }
  for (vector<int> t; s.size() > 2; q = t) {
    for (auto x : q) {
      for (auto e : T[x])
        if (--deg[e] == 1) t.push_back(e);
      s.erase(x);
    }
  }
  return s;
}
