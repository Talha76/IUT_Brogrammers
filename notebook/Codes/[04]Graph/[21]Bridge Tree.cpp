const int N = 1e5 + 1;
vector<int> g[N], tree[N];
int in[N], low[N], ptr, compId[N];
void go(int u, int p = -1) {
    in[u] = low[u] = ++ptr;
    for (int v: g[u]) {
        if (in[v]) {
            if (v == p) p = -1;
            else low[u] = min(low[u], in[v]);
        } else {
            go(v, u);
            low[u] = min(low[u], low[v]);
        }
    }
}
void shrink(int u, int id) {
    compId[u] = id;
    for (int v: g[u]) if (not compId[v]) {
        if (low[v] > in[u]) {
            tree[id].emplace_back(++ptr);
            tree[ptr].emplace_back(id);
            shrink(v, ptr);
        } else
            shrink(v, id);
    }
}
int main() {
  for (int i = 1; i <= n; ++i) if (!in[i]) go(i);
  vector <int> roots; ptr = 0;
  for (int i = 1; i <= n; ++i) if (!compId[i]) {
    roots.emplace_back(++ptr);
    shrink(i, ptr);
  }
}
