// Returns the vertex path using every edge once, or {}.
vector<int> directed_eulerian_path(int n, const vector<pii> &edges) {
    if(n == 0) return {};
    vector<vector<pii>> adj(n);
    vector<int> in(n), out(n), it(n), path;
    for(int i = 0; i < sz(edges); i++) {
        auto [u, v] = edges[i];
        adj[u].pb({v, i});
        out[u]++;
        in[v]++;
    }
    int s = -1, plus = 0, minus = 0;
    for(int u = 0; u < n; u++) {
        if(out[u] - in[u] == 1) s = u, plus++;
        else if(in[u] - out[u] == 1) minus++;
        else if(in[u] != out[u]) return {};
        if(s == -1 && out[u]) s = u;
    }
    if(!((plus == 1 && minus == 1) || (plus == 0 && minus == 0))) return {};
    if(edges.empty()) return {0};
    vector<int> st{s};
    while(!st.empty()) {
        int u = st.back();
        if(it[u] < sz(adj[u])) st.pb(adj[u][it[u]++].first);
        else path.pb(u), st.pop_back();
    }
    if(sz(path) != sz(edges) + 1) return {};
    reverse(all(path));
    return path;
}

vector<int> undirected_eulerian_path(int n, const vector<pii> &edges) {
    if(n == 0) return {};
    vector<vector<pii>> adj(n);
    vector<int> it(n), used(sz(edges)), path;
    for(int i = 0; i < sz(edges); i++) {
        auto [u, v] = edges[i];
        adj[u].pb({v, i});
        adj[v].pb({u, i});
    }
    int s = -1, odd = 0;
    for(int u = 0; u < n; u++) {
        if(sz(adj[u]) & 1) s = u, odd++;
        if(s == -1 && !adj[u].empty()) s = u;
    }
    if(odd != 0 && odd != 2) return {};
    if(edges.empty()) return {0};
    vector<int> st{s};
    while(!st.empty()) {
        int u = st.back();
        while(it[u] < sz(adj[u]) && used[adj[u][it[u]].second]) it[u]++;
        if(it[u] == sz(adj[u])) {
            path.pb(u);
            st.pop_back();
        } else {
            auto [v, id] = adj[u][it[u]++];
            used[id] = 1;
            st.pb(v);
        }
    }
    if(sz(path) != sz(edges) + 1) return {};
    reverse(all(path));
    return path;
}
