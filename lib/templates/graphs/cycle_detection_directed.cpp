vector<int> directed_cycle(const vector<vector<int>> &adj) {
    int n = sz(adj);
    vector<int> color(n), par(n, -1), cyc;
    int cu = -1, cv = -1;
    auto dfs = [&](this auto &&self, int u) -> bool {
        color[u] = 1;
        for(int v : adj[u]) {
            if(color[v] == 0) {
                par[v] = u;
                if(self(v)) return true;
            } else if(color[v] == 1) {
                cu = u;
                cv = v;
                return true;
            }
        }
        color[u] = 2;
        return false;
    };
    for(int i = 0; i < n && cv == -1; i++) {
        if(color[i] == 0) dfs(i);
    }
    if(cv == -1) return {};
    int x = cu;
    cyc.pb(cv);
    while(x != cv) {
        cyc.pb(x);
        x = par[x];
    }
    reverse(all(cyc));
    return cyc;
}
