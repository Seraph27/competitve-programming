struct trie {
    int cnt;
    vector<array<int, 26>> nex;
    vector<bool> exist;

    trie() { init(); }

    int make() {
        nex.eb();
        nex.back().fill(-1);
        exist.pb(false);
        return cnt++;
    }

    void init() {
        cnt = 0;
        nex.clear();
        exist.clear();
        make();
    }

    void insert(const string &s) {
        int vtx = 0;
        for(char c : s) {
            int d = c - 'a';
            int &nx = nex[vtx][d];
            if(nx == -1) nx = make();
            vtx = nx;
        }
        exist[vtx] = true;
    }

    bool contains(const string &s) const {
        int vtx = 0;
        for(char c : s) {
            int d = c - 'a';
            int nx = nex[vtx][d];
            if(nx == -1) return false;
            vtx = nx;
        }
        return exist[vtx];
    }

    // Shortest stored prefix of s, or s if none exists.
    string search(const string &s) const {
        int vtx = 0;
        string ans;
        for(char c : s) {
            int d = c - 'a';
            ans += c;
            int nx = nex[vtx][d];
            if(nx == -1) return s;
            vtx = nx;
            if(exist[vtx]) return ans;
        }
        return s;
    }
};
