#include <bits/stdc++.h>
#define int long long
#define ll long long
#define ar array
#define db double
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rint(l, r) uniform_int_distribution<int>(l, r)(rng)
template<typename T> bool ckmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.f); cerr << ','; __print(x.s); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

const int INF = 1<<30;
const int mod = 1e9+7;
const char nl = '\n';

void test_case() {
    int n, hp; cin >> n >> hp;
    vector<int> vi(n);
    for(auto&a: vi) cin >> a;
    sort(vi.rbegin(), vi.rend());

    int l = 0, r = INT_MAX, ans = 0; 
    int val;
    while(l + 1 < r){
        int m = (l+(r-l)/2);
        int tot = 0;
        
        tot+=(vi[0]*(m%2==0 ? m/2 : m/2+1) + vi[1]*(m/2));
        //cout << vi[1] << " " << m/2 << " " << vi[1]*(m/2 << nl;
        val = tot;
        if(tot < hp){
            l = m, ans = m;
        } else{
            r = m;
        }
    }
    debug(val);
    cout << ans + 1 << nl;
}

int32_t main() {    
    cin.tie(0)->sync_with_stdio(0);
    //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
    int t = 1;
    cin >> t;
    while (t--) test_case();
}
