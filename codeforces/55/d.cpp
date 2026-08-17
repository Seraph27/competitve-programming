// Problem: D. Beautiful numbers
// Contest: Codeforces Beta Round 51
// URL: https://codeforces.com/contest/55/problem/D
// Time Limit: 4000
// Start: Mon Aug 10 13:52:42 2026
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

int dp[20][50][1 << 12];
vc lcms;
int nxt[48][10];

void f() {
    for(int i = 1; i <= 2520; i++) {
        if(2520 % i == 0) lcms.pb(i);
    }

    for(int i = 0; i < 48; i++) {
        for(int d = 0; d <= 9; d++) {
            auto curr = lcms[i];
            auto nlcm = d ? lcm(curr, d) : curr;
            nxt[i][d] = lower_bound(all(lcms), nlcm) - lcms.begin();
        }
    }
    for(int id = 0; id < 48; id++) {
        for(int rem = 0; rem < 2520; rem++) {
            dp[0][id][rem] = rem % lcms[id] == 0;
        }
    }

    for(int len = 1; len <= 18; len++) {
        for(int id = 0; id < 48; id++) {
            for(int rem = 0; rem < 2520; rem++) {
                for(int d = 0; d <= 9; d++) {
                    int nid = nxt[id][d];
                    int nrem = (rem * 10 + d) % 2520;

                    dp[len][id][rem] += dp[len - 1][nid][nrem];
                }
            }
        }
    }
}

void shiina_mashiro() {
    int l, r; cin >> l >> r;

    auto f2 = [&](int v) {
        string s = to_string(v);
        reverse(all(s));
        int ans = 0, rem = 0;
        int id = 0;

        for(int i = sz(s) - 1; i >= 0; i--) {
            int digit = s[i] - '0';

            for(int d = 0; d < digit; d++) {
                int nrem = (rem * 10 + d) % 2520;
                int nid = nxt[id][d];
                ans += dp[i][nid][nrem];
            }

            rem = (rem * 10 + digit) % 2520;
            if(digit) id = nxt[id][digit];
        }

        ans += rem % lcms[id] == 0;
        return ans;
    };

    cout << f2(r) - f2(l - 1) << nl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    //freopen("perimeter.in","r",stdin); freopen("perimeter.out","w",stdout);
    int t = 1;
    cin >> t;
    f();
    while (t--) shiina_mashiro();
}
