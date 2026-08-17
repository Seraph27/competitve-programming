template<typename Add, typename Rem, typename Calc>
struct mo {
    int n, B;
    Add add; Rem rem; Calc calc;

    mo(int n_, int q, Add add_, Rem rem_, Calc calc_)
        : n(n_), B(max<int>(1, n_ / sqrt(q + 1) + 1)),
          add(add_), rem(rem_), calc(calc_) {}

    // queries: [l, r)
    template<typename Ans>
    vector<Ans> solve(const vector<pair<int,int>> &queries) {
        int q = sz(queries);
        vector<int> ord(q);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            int bi = queries[i].first / B, bj = queries[j].first / B;
            if (bi != bj) return bi < bj;
            return (bi & 1) ? queries[i].second > queries[j].second 
                              : queries[i].second < queries[j].second;
        });

        vector<Ans> ans(q);
        int cl = 0, cr = 0;
        for(int i : ord) {
            auto [l, r] = queries[i];
            while(cr < r) add(cr++);
            while(cl > l) add(--cl);
            while(cr > r) rem(--cr);
            while(cl < l) rem(cl++);
            ans[i] = calc();
        }
        return ans;
    }
};
