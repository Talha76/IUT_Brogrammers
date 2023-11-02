LL Hash(int u, int p) {
  vector<LL> childrenHash;
  for (auto v : adj[u]) if (v != p)
    childrenHash.add(Hash(v, u));
  sort(all(childrenHash));
  LL nodeHash = 0;
  for (int i = 0; i < childrenHash.size(); i++)
    nodeHash = (nodeHash + childrenHash[i] * bigmod(SEED, i, MOD)) % MOD;
  return nodeHash;
}
