struct TwoSAT {
    int n;
    vector<vector<int>> adj;

    TwoSAT(int n) : n(n), adj(2 * n) {}

    int id(int u, bool val) const {
        return 2 * u + val;
    }

    void either(int u, bool a, int v, bool b) {
        adj[id(u, !a)].pb(id(v, b));
        adj[id(v, !b)].pb(id(u, a));
    }

    void implies(int u, bool a, int v, bool b) {
        either(u, !a, v, b);
    }

    void set_value(int u, bool a) {
        either(u, a, u, a);
    }

    // either(u, a, v, b) adds (u == a) or (v == b).
    optional<vector<bool>> solve() const {
        int N = 2 * n;
        vector<vector<int>> rev(N);
        vector<int> vis(N), order, comp(N, -1);
        for(int u = 0; u < N; u++) {
            for(int v : adj[u]) rev[v].pb(u);
        }
        for(int s = 0; s < N; s++) {
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
        vector<bool> ans(n);
        for(int u = 0; u < n; u++) {
            if(comp[id(u, false)] == comp[id(u, true)]) return nullopt;
            ans[u] = comp[id(u, true)] > comp[id(u, false)];
        }
        return ans;
    }
};
