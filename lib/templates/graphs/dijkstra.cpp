// Nonnegative weights.
vector<int> dijkstra(int s, const vector<vector<pair<int,int>>> &adj) {
    int n = sz(adj);
    vector<int> dist(n, 4e18);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if(d != dist[u]) continue;
        for(auto [v, w] : adj[u]) {
            if(ckmin(dist[v], d + w)) pq.push({dist[v], v});
        }
    }
    return dist;
}
