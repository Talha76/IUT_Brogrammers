// tested by: https://judge.yosupo.jp/problem/staticrmq

// 0-based indexing, query finds in range [first, last]
#define lg(x) (31 - __builtin_clz(x))

const int N = 1e5 + 1;
const int K = lg(N);

int a[N], tr[N][K + 1];

namespace sparse_table {
  int f(int p1, int p2) { return min(p1, p2); }

  void build() {
    for(int i = 0; i < n; i++)
      tr[i][0] = a[i];
    for(int j = 1; j <= K; j++) {
      for(int i = 0; i + (1<<j) <= n; i++)
        tr[i][j] = f(tr[i][j - 1], tr[i + (1<<(j - 1))][j - 1]);
    }
  }

  int query(int l, int r) {
    int d = lg(r - l + 1);
    return f(table[l][d], table[r - (1<<d) + 1][d]);
  }
}
