struct HLD {
    int n, root, timer;
    const vector<vector<int>> &adj;
    vector<int> par, depth, size, heavy, head, pos, rev;

    // Connected tree; subtree(u) is its Euler-tour range.
    HLD(const vector<vector<int>> &adj, int root = 0)
        : n(sz(adj)), root(root), timer(0), adj(adj), par(n, -1), depth(n),
          size(n, 1), heavy(n, -1), head(n), pos(n), rev(n) {
        vector<int> order{root};
        par[root] = root;
        for(int i = 0; i < sz(order); i++) {
            int u = order[i];
            for(int v : adj[u]) {
                if(v == par[u]) continue;
                par[v] = u;
                depth[v] = depth[u] + 1;
                order.pb(v);
            }
        }
        for(int i = n - 1; i > 0; i--) {
            int u = order[i];
            size[par[u]] += size[u];
            if(heavy[par[u]] == -1 || size[u] > size[heavy[par[u]]]) heavy[par[u]] = u;
        }
        vector<pii> st{{root, root}};
        while(!st.empty()) {
            auto [u, h] = st.back();
            st.pop_back();
            for(int v = u; v != -1; v = heavy[v]) {
                head[v] = h;
                pos[v] = timer;
                rev[timer++] = v;
                for(int e : adj[v]) {
                    if(e != par[v] && e != heavy[v]) st.pb({e, e});
                }
            }
        }
    }

    int lca(int u, int v) const {
        while(head[u] != head[v]) {
            if(depth[head[u]] < depth[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }

    pii subtree(int u) const {
        return {pos[u], pos[u] + size[u]};
    }

    // {l, r, rev}: [l, r), rev means traverse right-to-left.
    vector<array<int, 3>> path(int u, int v, bool edge = false) const {
        vector<array<int, 3>> left, right;
        while(head[u] != head[v]) {
            if(depth[head[u]] >= depth[head[v]]) {
                left.pb({pos[head[u]], pos[u] + 1, 1});
                u = par[head[u]];
            } else {
                right.pb({pos[head[v]], pos[v] + 1, 0});
                v = par[head[v]];
            }
        }
        if(depth[u] >= depth[v]) left.pb({pos[v] + edge, pos[u] + 1, 1});
        else right.pb({pos[u] + edge, pos[v] + 1, 0});
        reverse(all(right));
        left.insert(left.end(), all(right));
        return left;
    }
};
