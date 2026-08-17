// FHQ treap for a sequence: insert/erase, range reverse/add/sum.
// All ranges are [l, r).
// FHQ tr; tr.build(a);
struct FHQ {
    struct Node { int ls, rs, sz, pri, val, sum, add; bool rev; };
    vector<Node> t;
    int root = 0;

    FHQ() { t.pb({0, 0, 0, 0, 0, 0, 0, false}); }

    int make(int v) {
        t.pb({0, 0, 1, (int)rng(), v, v, 0, false});
        return sz(t) - 1;
    }

    void pull(int x) {
        t[x].sz = t[t[x].ls].sz + t[t[x].rs].sz + 1;
        t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum + t[x].val;
    }

    void apply_add(int x, int v) {
        if(!x) return;
        t[x].val += v;
        t[x].sum += v * t[x].sz;
        t[x].add += v;
    }

    void apply_rev(int x) {
        if(!x) return;
        swap(t[x].ls, t[x].rs);
        t[x].rev ^= 1;
    }

    void push(int x) {
        if(t[x].add) {
            apply_add(t[x].ls, t[x].add);
            apply_add(t[x].rs, t[x].add);
            t[x].add = 0;
        }
        if(t[x].rev) {
            apply_rev(t[x].ls);
            apply_rev(t[x].rs);
            t[x].rev = false;
        }
    }

    void split(int x, int k, int &a, int &b) {
        if(!x) {
            a = b = 0;
            return;
        }
        push(x);
        if(t[t[x].ls].sz + 1 <= k) {
            a = x;
            split(t[x].rs, k - t[t[x].ls].sz - 1, t[x].rs, b);
        } else {
            b = x;
            split(t[x].ls, k, a, t[x].ls);
        }
        pull(x);
    }

    int merge(int a, int b) {
        if(!a || !b) return a | b;
        if(t[a].pri > t[b].pri) {
            push(a);
            t[a].rs = merge(t[a].rs, b);
            pull(a);
            return a;
        }
        push(b);
        t[b].ls = merge(a, t[b].ls);
        pull(b);
        return b;
    }

    template<class F>
    int range(int l, int r, F f) {
        int a, b, c;
        split(root, l, a, b);
        split(b, r - l, b, c);
        int res = f(b);
        root = merge(merge(a, b), c);
        return res;
    }

    void build(const vector<int> &a) {
        root = 0;
        for(int x : a) root = merge(root, make(x));
    }

    void insert(int pos, int v) {
        int a, b;
        split(root, pos, a, b);
        root = merge(merge(a, make(v)), b);
    }

    void erase(int l, int r) {
        int a, b, c;
        split(root, l, a, b);
        split(b, r - l, b, c);
        root = merge(a, c);
    }

    void reverse(int l, int r) {
        range(l, r, [&](int x) {
            apply_rev(x);
            return 0LL;
        });
    }

    void add(int l, int r, int v) {
        range(l, r, [&](int x) {
            apply_add(x, v);
            return 0LL;
        });
    }

    int sum(int l, int r) {
        return range(l, r, [&](int x) {
            return t[x].sum;
        });
    }

    void dump(int x, vector<int> &out) {
        if(!x) return;
        push(x);
        dump(t[x].ls, out);
        out.pb(t[x].val);
        dump(t[x].rs, out);
    }

    vector<int> to_vector() {
        vector<int> out;
        dump(root, out);
        return out;
    }
};
