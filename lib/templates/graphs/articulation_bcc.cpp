struct bcc_result {
    vector<int> articulation;
    vector<vector<int>> bcc;
};

// Undirected adjacency stores {vertex, edge id}; no self-loops.
bcc_result articulation_bcc(int n, const vector<vector<pii>> &adj) {
    vector<int> tin(n, -1), low(n), cut(n);
    vector<pii> stk;
    vector<vector<int>> bcc;
    int timer = 0;
    auto dfs = [&](this auto &&self, int u, int pe) -> void {
        tin[u] = low[u] = timer++;
        int child = 0;
        for(auto [v, id] : adj[u]) {
            if(id == pe) continue;
            if(tin[v] == -1) {
                child++;
                stk.pb({u, v});
                self(v, id);
                low[u] = min(low[u], low[v]);
                if(low[v] >= tin[u]) {
                    if(pe != -1 || child > 1) cut[u] = 1;
                    vector<int> cur;
                    while(true) {
                        auto [a, b] = stk.back();
                        stk.pop_back();
                        cur.pb(a);
                        cur.pb(b);
                        if(a == u && b == v) break;
                    }
                    sort(all(cur));
                    cur.erase(unique(all(cur)), cur.end());
                    bcc.pb(cur);
                }
            } else if(tin[v] < tin[u]) {
                low[u] = min(low[u], tin[v]);
                stk.pb({u, v});
            }
        }
    };
    for(int i = 0; i < n; i++) {
        if(tin[i] != -1) continue;
        dfs(i, -1);
        if(adj[i].empty()) bcc.pb({i});
    }
    vector<int> articulation;
    for(int i = 0; i < n; i++) {
        if(cut[i]) articulation.pb(i);
    }
    return {articulation, bcc};
}
