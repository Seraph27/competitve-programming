template<typename it, typename bin_op>
struct disjoint_sparse_table {
    using T = typename iterator_traits<it>::value_type;
    int n;
    vector<T> a;
    vector<vector<T>> t;
    bin_op F;

    disjoint_sparse_table(it first, it last, bin_op op) : n(distance(first, last)), a(first, last), F(op) {
        int lg = 0;
        while((1LL << lg) < n) lg++;
        t.assign(lg, vector<T>(n));
        for(int h = 0; h < lg; h++) {
            int len = 1LL << (h + 1);
            for(int l = 0; l < n; l += len) {
                int mid = min(l + (len >> 1), n);
                int r = min(l + len, n);
                if(l == mid) continue;
                t[h][mid - 1] = a[mid - 1];
                for(int i = mid - 2; i >= l; i--) t[h][i] = F(a[i], t[h][i + 1]);
                if(mid == r) continue;
                t[h][mid] = a[mid];
                for(int i = mid + 1; i < r; i++) t[h][i] = F(t[h][i - 1], a[i]);
            }
        }
    }

    // [l, r), associative
    T query(int l, int r) {
        assert(l < r);
        if(r - l == 1) return a[l];
        int h = 63 - __builtin_clzll(l ^ (r - 1));
        return F(t[h][l], t[h][r - 1]);
    }
};
