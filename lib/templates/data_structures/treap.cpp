// Treap for an ordered multiset: insert/erase, rank/kth, predecessor/successor.
// rank and kth are 1-indexed; pred and succ are strict.
// Treap tr; tr.insert(x);
struct Treap {
    struct Node { int ls, rs, val, pri, cnt, sz; };
    vector<Node> t;
    int root = 0;

    Treap() { t.pb({0, 0, 0, 0, 0, 0}); }

    int make(int v) {
        t.pb({0, 0, v, (int)rng(), 1, 1});
        return sz(t) - 1;
    }

    void pull(int x) {
        t[x].sz = t[t[x].ls].sz + t[t[x].rs].sz + t[x].cnt;
    }

    int rot_r(int x) {
        int y = t[x].ls;
        t[x].ls = t[y].rs;
        t[y].rs = x;
        pull(x);
        pull(y);
        return y;
    }

    int rot_l(int x) {
        int y = t[x].rs;
        t[x].rs = t[y].ls;
        t[y].ls = x;
        pull(x);
        pull(y);
        return y;
    }

    int ins(int x, int v) {
        if(!x) return make(v);
        if(t[x].val == v) {
            t[x].cnt++;
            pull(x);
            return x;
        }
        if(v < t[x].val) {
            t[x].ls = ins(t[x].ls, v);
            if(t[t[x].ls].pri > t[x].pri) x = rot_r(x);
        } else {
            t[x].rs = ins(t[x].rs, v);
            if(t[t[x].rs].pri > t[x].pri) x = rot_l(x);
        }
        pull(x);
        return x;
    }

    int del(int x, int v) {
        if(!x) return 0;
        if(v < t[x].val) t[x].ls = del(t[x].ls, v);
        else if(v > t[x].val) t[x].rs = del(t[x].rs, v);
        else {
            if(t[x].cnt > 1) {
                t[x].cnt--;
                pull(x);
                return x;
            }
            if(!t[x].ls || !t[x].rs) return t[x].ls | t[x].rs;
            if(t[t[x].ls].pri > t[t[x].rs].pri) {
                x = rot_r(x);
                t[x].rs = del(t[x].rs, v);
            } else {
                x = rot_l(x);
                t[x].ls = del(t[x].ls, v);
            }
        }
        pull(x);
        return x;
    }

    void insert(int v) { root = ins(root, v); }
    void erase(int v) { root = del(root, v); }

    int rank(int v) {
        int x = root, res = 0;
        while(x) {
            if(v <= t[x].val) x = t[x].ls;
            else {
                res += t[t[x].ls].sz + t[x].cnt;
                x = t[x].rs;
            }
        }
        return res + 1;
    }

    int kth(int k) {
        assert(1 <= k && k <= t[root].sz);
        int x = root;
        while(x) {
            int lsz = t[t[x].ls].sz;
            if(k <= lsz) x = t[x].ls;
            else if(k <= lsz + t[x].cnt) return t[x].val;
            else {
                k -= lsz + t[x].cnt;
                x = t[x].rs;
            }
        }
        return -1;
    }

    int pred(int v) {
        int x = root, res = -inf;
        while(x) {
            if(t[x].val < v) {
                res = t[x].val;
                x = t[x].rs;
            } else x = t[x].ls;
        }
        return res;
    }

    int succ(int v) {
        int x = root, res = inf;
        while(x) {
            if(t[x].val > v) {
                res = t[x].val;
                x = t[x].ls;
            } else x = t[x].rs;
        }
        return res;
    }
};
