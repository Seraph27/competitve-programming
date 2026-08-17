template<typename T> struct fenwick {
    int n; vector<T> bit;
    fenwick(int a) : n(a), bit(a + 1) {}

    // [0, pos)
    T sum(int pos) {
        T s = 0;
        for(; pos; s += bit[pos], pos -= pos & -pos);
        return s;
    }

    // [l, r)
    T query(int l, int r) {
        return sum(r) - sum(l);
    }

    void update(int pos, T x) {
        pos++;
        for(; pos <= n; bit[pos] += x, pos += pos & -pos);
    }

    // First pos with sum(pos + 1) >= k, requires nonnegative frequencies.
    int kth(T k) {
        int pos = 0;
        int pw = 1;
        while((pw << 1) <= n) pw <<= 1;
        for(; pw; pw >>= 1) {
            if(pos + pw <= n && bit[pos + pw] < k) {
                pos += pw;
                k -= bit[pos];
            }
        }
        return pos;
    }
};
