const int N = 1000006;
using DT = LL;
using LT = LL;
constexpr DT I = 0;
constexpr LT None = 0;
DT val[4 * N];
LT lazy[4 * N];
int L, R;
void pull(int s, int e, int u) {
  val[u] = val[u << 1] + val[u << 1 | 1];
}
void apply(const LT &uval, int s, int e, int u) {
  if (uval == None) return;
  val[u] += (e - s + 1) * uval;
  lazy[u] += uval;
}
void reset(int u) { lazy[u] = None; }
DT merge(const DT &a, const DT &b) { return a + b; }
DT get(int s, int e, int u) { return val[u]; }
void push(int s, int e, int u) {
  if (s == e) return;
  apply(lazy[u], s, s + e >> 1, u << 1);
  apply(lazy[u], s + e + 2 >> 1, e, u << 1 | 1);
  reset(u);
}
void build(int s, int e, vector<DT> &v, int u = 1) {
  lz[u] = None;
  if (s == e) {
    val[u] = v[s];
    return;
  }
  int m = s + e >> 1;
  build(s, m, v, u<<1);
  build(m + 1, e, v, u<<1|1);
  pull(s, e, u);
}
void update(int l, int r, LT uval, int s = L, int e = R, int u = 1) {
  if (l > e or s > r) return;
  if (l <= s and e <= r) {
    apply(uval, s, e, u);
    return;
  }
  push(s, e, u);
  int m = s+e >> 1;
  update(l, r, uval, s, m, u<<1);
  update(l, r, uval, m+1, e, u<<1|1);
  pull(s, e, u);
}
DT query(int l, int r, int s = L, int e = R, int u = 1) {
  if (l > e or s > r) return I;
  if (l <= s and e <= r) return get(s, e, u);
  push(s, e, u);
  int m = s+e >> 1;
  DT ql = query(l, r, s, m, u<<1),
     qr = query(l, r, m+1, e, u<<1|1);
  return merge(ql, qr);
}
void init(int _L, int _R, vector<DT> &v) {
  L = _L, R = _R;
  build(L, R, v);
}
