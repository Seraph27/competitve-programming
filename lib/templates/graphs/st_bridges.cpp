vector<pii> st_bridges(int n, const vector<vector<int>> &adj, int s, int t) {
    vector<int> tin(n, -1), low(n), vis(n), hasT(n);
    int timer = 0;
    vector<pii> res;

    auto dfs = [&](this auto &&self, int u, int p) -> void {
        vis[u] = 1;
        tin[u] = low[u] = timer++;
        hasT[u] = (u == t);
        bool skipped = false;
        for(int v : adj[u]) {
            if(v == p && !skipped) {
                skipped = true;
                continue;
            }
            if(vis[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                self(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] > tin[u] && hasT[v]) res.pb({u, v});
                hasT[u] |= hasT[v];
            }
        }
    };

    dfs(s, -1);
    return res;
}
