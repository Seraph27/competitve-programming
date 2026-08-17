struct LCA {
    int n, LOG, root;
    const vector<vector<int>> &adj;
    vector<int> depth;
    vector<vector<int>> up;

    // Connected tree rooted at root.
    LCA(const vector<vector<int>> &adj, int root = 0) : n(sz(adj)), LOG(0), root(root), adj(adj) {
        while ((1 << LOG) <= n) ++LOG;
        depth.assign(n, 0);
        up.assign(n, vector<int>(LOG, root));
        vector<int> par(n, root), st; st.pb(root);
        vector<int> vis(n, 0); vis[root] = 1;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            up[u][0] = par[u];
            for (int j = 1; j < LOG; j++) up[u][j] = up[up[u][j - 1]][j - 1];
            for (int v : adj[u]) if (!vis[v]) { vis[v] = 1; par[v] = u; depth[v] = depth[u] + 1; st.pb(v); }
        }
    }

    int jump(int u, int k) const {
        for (int j = 0; j < LOG; j++) if (k >> j & 1) u = up[u][j];
        return u;
    }

    int lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        u = jump(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; j--) if (up[u][j] != up[v][j]) { u = up[u][j]; v = up[v][j]; }
        return up[u][0];
    }

    int dist(int u, int v) const {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }
};
