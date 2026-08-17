// Problem: D. A Ribbon for Tomorrow
// Contest: Codeforces Round 1116 (Div. 2)
// URL: https://codeforces.com/contest/2256/problem/D
// Time Limit: 2000
// Start: Sun Aug  9 09:29:54 2026
// multitest
#ifdef MISAKA
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

#define int long long
#define sz(x) (int)x.size()
#define ar array
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define db double

using namespace std;
using vc = vector<int>;
using vvc = vector<vc>;
using vvvc = vector<vvc>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rint(l, r) uniform_int_distribution<int>(l, r)(rng)

template<typename T> bool ckmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template<typename T, typename S> constexpr T ifloor(const T a, const S b){return a/b-(a%b&&(a^b)<0);}
template<class T, class S> constexpr T iceil(T a, S b) { return -ifloor(-a, b); }
template<typename T> T isqrt(T x) { T y = sqrtl((long double)x); while((__int128)(y+1)*(y+1) <= x) y++; while((__int128)y*y > x) y--; return y; }

template<typename T> void sort_unique(vector<T> &vec){ sort(vec.begin(),vec.end()); vec.resize(unique(vec.begin(),vec.end())-vec.begin()); }
template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) {for (auto &x : v) os << x << " "; return os;}
template<typename T> void read(vector<T> &a) { for(auto &x : a) cin >> x; }
template<typename T> void print(const vector<T> &a) { for(int i = 0; i < sz(a); i++) cout << a[i] << " \n"[i == sz(a) - 1]; }

template<class F> int first_true(int L, int R, F ok) { while (R - L > 1) { int mid = (L + R) / 2; if (ok(mid)) R = mid; else L = mid; } return R; }
template<class F> int last_true(int L, int R, F ok) { while (R - L > 1) { int mid = (L + R) / 2; if (ok(mid)) L = mid; else R = mid; } return L; }

template<class T> vector<T> prefix(const vector<T> &a) { vector<T> pref(sz(a) + 1); for(int i = 0; i < sz(a); i++) pref[i + 1] = pref[i] + a[i]; return pref; }
template<class T> T rangesum(const vector<T> &pref, int L, int R) { return pref[R] - pref[L]; }

vvc read_graph(int n, int m, bool one = true) { vvc adj(n); for(int i = 0; i < m; i++) { int u, v; cin >> u >> v; if (one) u--, v--; adj[u].pb(v); adj[v].pb(u); } return adj; }
vvc read_digraph(int n, int m, bool one = true) { vvc adj(n); for(int i = 0; i < m; i++) { int u, v; cin >> u >> v; if (one) u--, v--; adj[u].pb(v); } return adj; }
vvc read_tree(int n, bool one = true) { return read_graph(n, n - 1, one); }

int topbit(long long x) { return x == 0 ? -1 : 63 - __builtin_clzll(x); }
int lowbit(long long x) { return x == 0 ? 64 : __builtin_ctzll(x); }
int popcnt(long long x) { return __builtin_popcountll(x); }
bool ispow2(long long x) { return x > 0 && (x & -x) == x; }
long long mask(int k) { return (1LL << k) - 1; }

#ifdef MISAKA
struct _debug {
template<typename T, size_t N> static void __print(const T (&a)[N]) { cerr << '{'; for (size_t i = 0; i < N; ++i) { if (i) cerr << ',';__print(a[i]); }cerr << '}'; }
template<typename T> static void __print(const T &x) {
    if constexpr (is_convertible_v<T, string> || is_fundamental_v<T>) cerr << x;
    else { cerr << '{'; int f{}; for (auto i : x) cerr << (f++?",":""), __print(i); cerr << '}'; }
}
template<typename T, typename V>
static void __print(const pair<T, V> &x) { cerr << '(', __print(x.first), cerr << ',', __print(x.second), cerr << ')'; }
template<typename T, typename... V>
static void _print(const T& t, const V&... v) { __print(t); if constexpr (sizeof...(v)) cerr << ", ", _print(v...); else cerr << "]\n"; }
};
#define debug(x...) cerr << "[" << #x << "] = [", _debug::_print(x)
#else
#define debug(x...)
#endif

const char nl = '\n';
const int inf = 0x3f3f3f3f3f3f3f3fLL;

template <int MOD_> struct modnum {
    static constexpr int MOD = MOD_;

    int v;

    modnum() : v(0) {}
    modnum(int v_) : v(v_ % MOD) { if (v < 0) v += MOD; }

    explicit operator int() const { return v; }
    explicit operator bool() const { return v; }

    friend ostream& operator << (ostream& out, const modnum& n) { return out << n.v; }
    friend istream& operator >> (istream& in, modnum& n) { int v_; in >> v_; n = modnum(v_); return in; }

    friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
    friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

    modnum operator- () const {
        return neg();
    }
    modnum operator+ () const {
        return modnum(*this);
    }

    modnum& operator ++ () {
        v++;
        if (v == MOD) v = 0;
        return *this;
    }
    modnum& operator -- () {
        if (v == 0) v = MOD;
        v--;
        return *this;
    }
    modnum& operator += (const modnum& o) {
        v -= MOD-o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator -= (const modnum& o) {
        v -= o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator *= (const modnum& o) {
        v = v * o.v % MOD;
        return *this;
    }

    friend modnum binpow(modnum a, int p) {
        if (p == 0) return 1;
        modnum ret = 1;
        for (; p; p /= 2, a *= a) if (p&1) ret *= a;
        return ret;
    }

    // MOD must be prime and v must be nonzero.
    modnum inv() const {
        return binpow(*this, MOD-2);
    }
    friend modnum inv(const modnum& m) { return m.inv(); }

    modnum& operator /= (const modnum& o) {
        return *this *= o.inv();
    }

    modnum neg() const {
        modnum res;
        res.v = v ? MOD-v : 0;
        return res;
    }
    friend modnum neg(const modnum& m) { return m.neg(); }

    friend modnum operator ++ (modnum& a, int32_t) { modnum r = a; ++a; return r; }
    friend modnum operator -- (modnum& a, int32_t) { modnum r = a; --a; return r; }
    friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
    friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
    friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
    friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};

const int mod = 998244353;
using mint = modnum<mod>;

vector<mint> facs, invfacs;

mint choose(int _a, int _b) {
    if (_b > _a || _a < 0 || _b < 0) return 0;
    return facs[_a] * invfacs[_b] * invfacs[_a-_b];
}

void finit(const int nx) {
    facs.assign(nx + 1, 1);
    invfacs.assign(nx + 1, 1);
    for(int i = 1; i <= nx; i++) facs[i] = facs[i - 1] * mint(i);
    invfacs[nx] = inv(facs[nx]);
    for(int i = nx; i >= 1; i--) invfacs[i - 1] = invfacs[i] * mint(i);
}

void shiina_mashiro() {
    int n; cin >> n;
    string s; cin >> s;
    s.push_back('.');
    int zero = 0, one = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] != s[i + 1]){
            if(s[i] == '0') zero++;
            else one++;
        }
    }

    mint ans = 1;

    int z = count(all(s), '0');
    int o = n - z;

    if(z and zero) ans *= choose(z - 1, zero - 1);
    if(o and one) ans *= choose(o - 1, one - 1);

    cout << ans.v << nl;
     
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    //freopen("perimeter.in","r",stdin); freopen("perimeter.out","w",stdout);
    int t = 1;
    cin >> t;
    finit(1e6);
    while (t--) shiina_mashiro();
}
