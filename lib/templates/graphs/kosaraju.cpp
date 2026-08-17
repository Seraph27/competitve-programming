// comp ids follow the condensation DAG.
pair<int, vector<int>> kosaraju(const vector<vector<int>> &adj) {
    int n = sz(adj);
    vector<vector<int>> rev(n);
    vector<int> vis(n), order, comp(n, -1);
    for(int u = 0; u < n; u++) {
        for(int v : adj[u]) rev[v].pb(u);
    }
    for(int s = 0; s < n; s++) {
        if(vis[s]) continue;
        vector<pii> st{{s, 0}};
        vis[s] = 1;
        while(!st.empty()) {
            auto &[u, i] = st.back();
            if(i < sz(adj[u])) {
                int v = adj[u][i++];
                if(!vis[v]) {
                    vis[v] = 1;
                    st.pb({v, 0});
                }
            } else {
                order.pb(u);
                st.pop_back();
            }
        }
    }
    reverse(all(order));
    int cnt = 0;
    for(int s : order) {
        if(comp[s] != -1) continue;
        vector<int> st{s};
        comp[s] = cnt;
        while(!st.empty()) {
            int u = st.back();
            st.pop_back();
            for(int v : rev[u]) {
                if(comp[v] == -1) {
                    comp[v] = cnt;
                    st.pb(v);
                }
            }
        }
        cnt++;
    }
    return {cnt, comp};
}
