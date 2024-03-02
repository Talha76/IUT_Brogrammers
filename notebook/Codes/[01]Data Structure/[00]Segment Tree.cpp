namespace segtree {
  const int N = 1000006;

  using DT = long long;
  using LT = long long;
  constexpr DT I = 0; 
  constexpr LT None = 0;

  DT val[N<<2];
  LT lz[N<<2];
  int L, R;
  void apply(int u, const LT &U, int l, int r) {
    if (U != None) val[u] += (r - l + 1) * U;
    lz[u] += U;
  }
  DT merge(const DT &a, const DT &b, int l, int r) {
    return a + b;
  }
  /* -- Do Not Touch Anything Below This -- */

  void push(int l, int r, int u) {
    if(l == r) return;
    apply(u << 1, lz[u], l, (l + r) >> 1);
    apply(u << 1 | 1, lz[u], (l + r + 2) >> 1, r);
    lz[u] = None;
  }
  void build(int l, int r, vector <DT> const &v, int u = 1 ) {
    lz[u] = None;
    if(l == r) {
      val[u] = v[l];
      return;
    }
    int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
    build(l, m, v, lft);
    build(m + 1, r, v, ryt);
    val[u] = merge(val[lft], val[ryt], l, r);
  }
  void update(int ql,int qr, LT uval, int l = L, int r = R, int u = 1) {
    if (qr < l or ql > r) return;
    if(ql <= l and r <= qr) {
      apply(u, uval, l, r);
      return;
    }
    push(l, r, u);
    int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
    update(ql, qr, uval,  l,  m, lft);
    update(ql, qr, uval, m + 1, r, ryt);
    val[u] = merge(val[lft], val[ryt], l, r);
  }
  DT query(int ql, int qr, int l = L, int r = R, int u = 1) {
    if (qr < l or ql > r) return I;
    if (ql <= l and r <= qr) return val[u];
    push(l, r, u);
    int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
    DT ansl = query(ql, qr, l, m, lft);
    DT ansr = query(ql, qr, m + 1, r, ryt);
    return merge(ansl, ansr, l, r);
  }
  void init(int _L, int _R, vector <DT> v) {
    L = _L, R = _R;
    build(L, R, v);
  }
};
