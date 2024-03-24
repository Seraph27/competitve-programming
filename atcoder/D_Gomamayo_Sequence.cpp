#include <bits/stdc++.h>
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
void __print(long long x) {cerr << x;}
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

const int mod = 1e9+7;
const int INF = 1001001001;
const ll INFLL = 100100100100100100;
const char nl = '\n';

void test_case() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> vi(n);
    for(auto&a: vi) cin >> a;
    ll ans = INFLL;
    vector<ll> f0(n+1), f1(n+1), g0(n+1), g1(n+1);
    for(int i = 0; i < n; i++){
        f0[i+1] = f0[i];
        f1[i+1] = f1[i];
        if(i%2==0){
            if(s[i]=='0'){
                f1[i+1]+=vi[i];
            } else{
                f0[i+1]+=vi[i];
            }
        } else{
            if(s[i]=='0'){
                f0[i+1]+=vi[i];
            } else{
                f1[i+1]+=vi[i];
            }
        }
    }
    for(int j = n-1; j>0; j--){
        g0[j] = g0[j+1];
        g1[j] = g1[j+1];
        if(j%2==0){
            if(s[j]=='0'){
                g0[j]+=vi[j];
            } else{
                g1[j]+=vi[j];
            }
        } else{
            if(s[j]=='0'){
                g1[j]+=vi[j];
            } else{
                g0[j]+=vi[j];
            }
        }
    }
    debug(f0, g0, f1, g1);
    for(int i = 1; i < n; i++) ans = min(ans, f0[i]+g0[i]); 
    for(int i = 1; i < n; i++) ans = min(ans, f1[i]+g1[i]);

    cout << ans << nl;
}

int main() {    
    cin.tie(0)->sync_with_stdio(0);
    //freopen("cardgame.in","r",stdin); freopen("cardgame.out","w",stdout);  //ucsao
    int t = 1;
    //cin >> t;
    while (t--) test_case();
}


