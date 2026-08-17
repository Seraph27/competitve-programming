template<class T, class U, class Monoid, class LazyApply, class LazyCombine>
struct lazy_segtree {
    int n;
    vector<T> tree;
    vector<U> lazy;
    vector<int> size;
    vector<bool> marked;
    Monoid op;
    T e;
    LazyApply apply_lazy;
    LazyCombine combine_lazy;

    lazy_segtree(int n, Monoid op, T e, LazyApply apply_lazy, LazyCombine combine_lazy)
        : n(n), tree(4 * n, e), lazy(4 * n), size(4 * n), marked(4 * n),
          op(op), e(e), apply_lazy(apply_lazy), combine_lazy(combine_lazy) {
        assert(n > 0);
        build(1, 0, n, nullptr);
    }

    lazy_segtree(const vector<T> &a, Monoid op, T e, LazyApply apply_lazy, LazyCombine combine_lazy)
        : n(sz(a)), tree(4 * n, e), lazy(4 * n), size(4 * n), marked(4 * n),
          op(op), e(e), apply_lazy(apply_lazy), combine_lazy(combine_lazy) {
        assert(n > 0);
        build(1, 0, n, &a);
    }

    void build(int node, int nl, int nr, const vector<T> *a) {
        size[node] = nr - nl;
        if(nr - nl == 1) {
            if(a) tree[node] = (*a)[nl];
            return;
        }
        int mid = (nl + nr) / 2;
        build(node * 2, nl, mid, a);
        build(node * 2 + 1, mid, nr, a);
        tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
    }

    void apply(int node, U v) {
        tree[node] = apply_lazy(tree[node], v, size[node]);
        if(marked[node]) lazy[node] = combine_lazy(lazy[node], v);
        else lazy[node] = v, marked[node] = true;
    }

    void push(int node) {
        if(!marked[node] || size[node] == 1) return;
        apply(node * 2, lazy[node]);
        apply(node * 2 + 1, lazy[node]);
        marked[node] = false;
    }

    void update(int node, int nl, int nr, int ql, int qr, U v) {
        if(qr <= nl || nr <= ql) return;
        if(ql <= nl && nr <= qr) {
            apply(node, v);
            return;
        }
        push(node);
        int mid = (nl + nr) / 2;
        update(node * 2, nl, mid, ql, qr, v);
        update(node * 2 + 1, mid, nr, ql, qr, v);
        tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
    }

    T query(int node, int nl, int nr, int ql, int qr) {
        if(qr <= nl || nr <= ql) return e;
        if(ql <= nl && nr <= qr) return tree[node];
        push(node);
        int mid = (nl + nr) / 2;
        return op(query(node * 2, nl, mid, ql, qr), query(node * 2 + 1, mid, nr, ql, qr));
    }

    // [l, r), combine_lazy(a, b) applies a then b
    void update(int l, int r, U v) { update(1, 0, n, l, r, v); }
    T query(int l, int r) { return query(1, 0, n, l, r); }
};

// auto op = [](int a, int b) { return a + b; };
// auto apply = [](int val, int add, int size) { return val + add * size; };
// auto combine = [](int a, int b) { return a + b; };
// lazy_segtree<int, int, decltype(op), decltype(apply), decltype(combine)> st(a, op, 0, apply, combine);
