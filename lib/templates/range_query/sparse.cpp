template<typename it, typename bin_op>
struct sparse_table {
    using T = typename iterator_traits<it>::value_type;
    vector<vector<T>> t; bin_op F;

    sparse_table(it first, it last, bin_op op) : F(op) {
        int n = distance(first, last);
        assert(n > 0);
        int lg = 1;
        while((1LL << lg) <= n) lg++;
        t.assign(lg, vector<T>(n));
        t[0].assign(first, last);
        for(int i = 1; i < sz(t); i++) {
            for(int j = 0; j + (1LL << i) <= n; j++) {
                t[i][j] = F(t[i - 1][j], t[i - 1][j + (1LL << (i - 1))]);
            }
        }
    }

    // [l, r), associative + idempotent
    T query(int l, int r) {
        assert(l < r);
        int h = 63 - __builtin_clzll(r - l);
        return F(t[h][l], t[h][r - (1LL << h)]);
    }
};
