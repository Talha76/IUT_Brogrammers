// Define random(l, r) function
typedef pair<long long, long long> PLL;
namespace TreeHash {
    PLL operator + (PLL a, PLL b) { return {a.first+b.first, a.second+b.second}; }
    PLL operator * (PLL a, PLL b) { return {a.first*b.first, a.second*b.second}; }
    PLL operator % (PLL a, int b) { return {a.first%b, a.second%b}; }
    using Tree = vector<vector<int>>;
    constexpr int N = 1e5, MAX = 1e9, MOD = 1e9 + 7;
    PLL val[N+1]{{1, 1}};
    void init() {
        set<PLL> s;
        for (int i = 1; i <= N; i++) {
            PLL v{random(1, MAX), random(1, MAX)};
            while (s.count(v)) v = {random(1, MAX), random(1, MAX)};
            val[i] = v;
        }
    }
    int hash(Tree const& g, vector<PII>& hashList, int u, int p = -1) {
        int h = 0;
        vector<PII> hashes;
        for (auto v: g[u]) if (v xor p) {
            h = max(h, hash(g, hashList, v, u));
            hashes.emplace_back(hashList[v]);
        }
        hashList[u] = {1, 1};
        for (auto e: hashes)
            hashList[u] = hashList[u] * (val[h] + e) % MOD;
        return h + 1;
    }
    vector<PII> hashList(Tree const& g, int root) {
        vector<PII> hashList(g.size());
        hash(g, hashList, root);
        return hashList;
    }
    bool is_isomorphic(Tree g1, Tree g2) {
        auto c1 = Diameter::find_center(g1), c2 = Diameter::find_center(g2);
        assert(max(c1.size(), c2.size()) < 3);
        for (auto e: c2) {
            auto h1 = hashList(g1, c1[0]),
                 h2 = hashList(g2, e);
            if (h1[c1[0]] == h2[e]) return true;
        }
        return false;
    }
}
