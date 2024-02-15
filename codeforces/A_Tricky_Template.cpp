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

const char nl = '\n';

void test_case() {
    int n; cin >> n;
    string a, b, c; cin >> a >> b >> c;
    bool match = true;
    for(int i = 0; i < n; i++){
        if(a[i] == b[i]){
            if(c[i] == a[i]){
                match = false;
            } else{
                match = true;
                break;
            }
        } else{
            if(c[i] == a[i] || c[i] == b[i]){
                match = false;
            } else{
                match = true; 
                break;
            }
        }
    }

    cout << (match ? "YES" : "NO") << nl;
}

int main() {    
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) test_case();
}

