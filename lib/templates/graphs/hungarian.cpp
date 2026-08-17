// Minimum-cost assignment, requires rows <= columns.
pair<int, vector<int>> hungarian(const vector<vector<int>> &a) {
    if(a.empty()) return {0, {}};
    int n = sz(a), m = sz(a[0]);
    assert(n <= m);
    vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
    for(int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m + 1, 4e18), used(m + 1);
        do {
            used[j0] = 1;
            int i0 = p[j0], delta = 4e18, j1 = 0;
            for(int j = 1; j <= m; j++) {
                if(used[j]) continue;
                int cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if(cur < minv[j]) minv[j] = cur, way[j] = j0;
                if(minv[j] < delta) delta = minv[j], j1 = j;
            }
            for(int j = 0; j <= m; j++) {
                if(used[j]) u[p[j]] += delta, v[j] -= delta;
                else minv[j] -= delta;
            }
            j0 = j1;
        } while(p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while(j0);
    }
    vector<int> match(n, -1);
    for(int j = 1; j <= m; j++) {
        if(p[j]) match[p[j] - 1] = j - 1;
    }
    return {-v[0], match};
}
