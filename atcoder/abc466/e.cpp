// Problem: E - Range Flip
// Contest: AtCoder Beginner Contest 466
// URL: https://atcoder.jp/contests/abc466/tasks/abc466_e
// Time Limit: 2000
// Start: Fri Jul 17 18:22:43 2026
// atcoder
#ifdef MISAKA
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#include <atcoder/modint>

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
using namespace atcoder;
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

using mint = modint998244353;
const char nl = '\n';
const int inf = 0x3f3f3f3f3f3f3f3fLL;

void shiina_mashiro() {
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    vvc dp(k + 2, vc(2, -inf));
    dp[0][0] = 0;

    for(int i = 0; i < n; i++) {
        vvc ndp(k + 2, vc(2, -inf));
        for(int j = 0; j <= k; j++) {
            ckmax(ndp[j][0], dp[j][0] + a[i]);
            ckmax(ndp[j + 1][1], dp[j][0] + b[i]);
            ckmax(ndp[j][0], dp[j][1] + a[i]);
            ckmax(ndp[j][1], dp[j][1] + b[i]);
        }

        swap(dp, ndp);
    }

    int ans = -inf;
    for(int i = 0; i <= k; i++) {
        ckmax(ans, max(dp[i][0], dp[i][1]));
    }
    cout << ans << nl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    //freopen("perimeter.in","r",stdin); freopen("perimeter.out","w",stdout);
    int t = 1;
    //cin >> t;
    while (t--) shiina_mashiro();
}
