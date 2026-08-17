template<class T, class Monoid>
struct segtree {
    int n;
    vector<T> t;
    Monoid op;
    T e;

    segtree(int n, Monoid op, T e) : n(n), t(2 * n, e), op(op), e(e) {
        assert(n > 0);
    }
    segtree(const vector<T> &a, Monoid op, T e) : n(sz(a)), t(2 * n, e), op(op), e(e) {
        assert(n > 0);
        copy(all(a), t.begin() + n);
        build();
    }

    void build() {
        for(int i = n - 1; i > 0; i--) t[i] = op(t[i << 1], t[i << 1 | 1]);
    }

    void update(int p, T val) {
        t[p += n] = val;
        while(p > 1) {
            p >>= 1;
            t[p] = op(t[p << 1], t[p << 1 | 1]);
        }
    }

    // [l, r)
    T query(int l, int r) {
        T left = e, right = e;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) left = op(left, t[l++]);
            if(r & 1) right = op(t[--r], right);
        }
        return op(left, right);
    }
};

// auto op = [](int a, int b) { return max(a, b); };
// segtree<int, decltype(op)> st(a, op, -inf);
