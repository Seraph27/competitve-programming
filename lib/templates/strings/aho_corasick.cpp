// Lowercase patterns. match returns {ending position, pattern id}.
struct aho_corasick {
    struct node {
        array<int, 26> nex;
        int link = 0, exit = 0;
        vector<int> out;
        node() { nex.fill(-1); }
    };

    vector<node> t{1};
    bool built = false;

    void insert(const string &s, int id) {
        assert(!built);
        int vtx = 0;
        for(char c : s) {
            int d = c - 'a';
            if(t[vtx].nex[d] == -1) {
                t[vtx].nex[d] = sz(t);
                t.eb();
            }
            vtx = t[vtx].nex[d];
        }
        t[vtx].out.pb(id);
    }

    void build() {
        assert(!built);
        built = true;
        queue<int> q;
        for(int d = 0; d < 26; d++) {
            int v = t[0].nex[d];
            if(v == -1) t[0].nex[d] = 0;
            else q.push(v);
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            int p = t[u].link;
            t[u].exit = t[p].out.empty() ? t[p].exit : p;
            for(int d = 0; d < 26; d++) {
                int v = t[u].nex[d];
                if(v == -1) {
                    t[u].nex[d] = t[p].nex[d];
                } else {
                    t[v].link = t[p].nex[d];
                    q.push(v);
                }
            }
        }
    }

    vector<pii> match(const string &s) const {
        assert(built);
        vector<pii> ans;
        int vtx = 0;
        for(int i = 0; i < sz(s); i++) {
            vtx = t[vtx].nex[s[i] - 'a'];
            for(int u = vtx; u; u = t[u].exit) {
                for(int id : t[u].out) ans.pb({i, id});
            }
        }
        return ans;
    }
};
