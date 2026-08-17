// Iterative Tarjan; comp ids follow the condensation DAG.
pair<int, vector<int>> tarjan(const vector<vector<int>> &adj) {
    int n = sz(adj), timer = 0, cnt = 0;
    vector<int> tin(n, -1), low(n), par(n, -1), comp(n, -1), stk;
    vector<bool> on(n);
    for(int s = 0; s < n; s++) {
        if(tin[s] != -1) continue;
        vector<pii> dfs{{s, 0}};
        tin[s] = low[s] = timer++;
        stk.pb(s);
        on[s] = true;
        while(!dfs.empty()) {
            auto &[u, i] = dfs.back();
            if(i < sz(adj[u])) {
                int v = adj[u][i++];
                if(tin[v] == -1) {
                    par[v] = u;
                    tin[v] = low[v] = timer++;
                    stk.pb(v);
                    on[v] = true;
                    dfs.pb({v, 0});
                } else if(on[v]) {
                    low[u] = min(low[u], tin[v]);
                }
            } else {
                dfs.pop_back();
                if(par[u] != -1) low[par[u]] = min(low[par[u]], low[u]);
                if(low[u] == tin[u]) {
                    while(true) {
                        int v = stk.back();
                        stk.pop_back();
                        on[v] = false;
                        comp[v] = cnt;
                        if(v == u) break;
                    }
                    cnt++;
                }
            }
        }
    }
    for(int &x : comp) x = cnt - 1 - x;
    return {cnt, comp};
}
