struct hopcroftkarp {
    int nL, nR, D;
    vector<vector<int>> adj;
    vector<int> matchL, matchR, dist;

    hopcroftkarp(int nL, int nR) : nL(nL), nR(nR), adj(nL), matchL(nL, -1), matchR(nR, -1), dist(nL) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
    }

    bool bfs() {
        queue<int> q;
        D = -1;
        fill(all(dist), -1);
        for(int u = 0; u < nL; u++) if(matchL[u] == -1) dist[u] = 0, q.push(u);
        while(!q.empty()) {
            auto f = q.front(); q.pop();
            if(D != -1 && dist[f] + 1 >= D) continue;
            for(int e : adj[f]) {
                int v = matchR[e];
                if(v == -1) D = dist[f] + 1;
                else if(dist[v] == -1) {
                    dist[v] = dist[f] + 1;
                    q.push(v);
                }
            }
        }
        return D != -1;
    }

    bool dfs(int u) {
        for(int e : adj[u]) {
            int v = matchR[e];
            if((v == -1 && dist[u] + 1 == D) || (v != -1 && dist[v] == dist[u] + 1 && dfs(v))) {
                matchL[u] = e;
                matchR[e] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int res = 0;
        while(bfs()) {
            for(int u = 0; u < nL; u++) {
                if(matchL[u] == -1 && dfs(u)) ++res;
            }
        }
        return res;
    }
};
