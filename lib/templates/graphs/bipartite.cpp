bool bipartite(const vector<vector<int>> &adj, vector<int> &color) {
    int n = sz(adj);
    color.assign(n, -1);
    for(int s = 0; s < n; s++) {
        if(color[s] != -1) continue;
        queue<int> q;
        color[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int e : adj[u]) {
                if(color[e] == -1) {
                    color[e] = color[u] ^ 1;
                    q.push(e);
                } else if(color[e] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}
