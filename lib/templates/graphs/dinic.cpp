struct Dinic {
    struct Edge { int to, rev, cap; bool real; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> level, it;

    Dinic(int n): n(n), g(n), level(n), it(n) {}

    void add_edge(int u, int v, int c) {
        Edge a{v, (int)g[v].size(), c, true};
        Edge b{u, (int)g[u].size(), 0, false};
        g[u].pb(a);
        g[v].pb(b);
    }

    bool bfs() {
        fill(all(level), -1);
        queue<int> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u]) if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
        return level[t] >= 0;
    }

    int dfs(int u, int f) {
        if (!f || u == t) return f;
        for (int &i = it[u]; i < sz(g[u]); i++) {
            auto &e = g[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                int pushed = dfs(e.to, min(f, e.cap));
                if (pushed) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    int max_flow(int S, int T) {
        s = S; t = T;
        int flow = 0;
        while (bfs()) {
            fill(all(it), 0);
            while (int pushed = dfs(s, 4e18)) flow += pushed;
        }
        return flow;
    }

    // Destructively decomposes integral flow into unit S-T paths.
    vector<vector<int>> recover_path(int S, int T) {
        vector<vector<int>> paths;
        while (true) {
            vector<int> par_v(n, -1), par_e(n, -1);
            queue<int> q; q.push(S); par_v[S] = S;
            while (!q.empty() && par_v[T] == -1) {
                int u = q.front(); q.pop();
                for (int i = 0; i < sz(g[u]); i++) {
                    auto &e = g[u][i];
                    if (par_v[e.to] == -1 && e.real && g[e.to][e.rev].cap > 0) {
                        par_v[e.to] = u; par_e[e.to] = i;
                        q.push(e.to);
                    }
                }
            }
            if (par_v[T] == -1) break;
            vector<int> path;
            for (int v = T; v != S; v = par_v[v]) path.pb(v);
            path.pb(S);
            reverse(all(path));
            for (int v = T; v != S; v = par_v[v]) {
                int u = par_v[v], i = par_e[v];
                auto &e = g[u][i];
                e.cap += 1;
                g[e.to][e.rev].cap -= 1;
            }
            paths.pb(path);
        }
        return paths;
    }
};
