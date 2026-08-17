struct DSU {
    vector<int> f, siz;

    DSU() {}
    DSU(int n) { init(n); }

    void init(int n) {
        f.resize(n);
        iota(all(f), 0);
        siz.assign(n, 1);
    }

    int find(int x) {
        while(x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int size(int x) {
        return siz[find(x)];
    }
};
