const int b_N = 2;
const array<int, b_N> hash_mod{1000000007, 1000000009};
bool init_ = false;
array<int, b_N> bases;

int binpow(int a, int b, int mod) {
    int r = 1;
    for(; b; b >>= 1, a = (long long)a * a % mod) {
        if(b & 1) r = (long long)r * a % mod;
    }
    return r;
}

void init() {
    for(int i = 0; i < b_N; i++) bases[i] = rint(256, hash_mod[i] - 2);
}

// Double randomized polynomial hash: Hash h(s); h.query(l, r) uses [l, r).
template<typename T>
struct Hash {
    array<vector<int>, b_N> pref, inv;

    Hash(const T &s) {
        if(!init_) init(), init_ = true;
        int n = sz(s);
        for(int i = 0; i < b_N; i++) {
            int mod = hash_mod[i];
            pref[i].assign(n + 1, 0);
            inv[i].assign(n + 1, 1);
            int b = 1, ib = binpow(bases[i], mod - 2, mod);
            for(int j = 0; j < n; j++, b = (long long)b * bases[i] % mod) {
                int x = static_cast<int>(s[j]) + 1;
                x %= mod;
                if(x < 0) x += mod;
                pref[i][j + 1] = (pref[i][j] + (long long)b * x) % mod;
                inv[i][j + 1] = (long long)inv[i][j] * ib % mod;
            }
        }
    }

    array<int, b_N> query(int l, int r) const {
        array<int, b_N> ret;
        for(int i = 0; i < b_N; i++) {
            int mod = hash_mod[i];
            ret[i] = pref[i][r] - pref[i][l];
            if(ret[i] < 0) ret[i] += mod;
            ret[i] = (long long)ret[i] * inv[i][l] % mod;
        }
        return ret;
    }
};
