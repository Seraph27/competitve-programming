vector<int> prefix_function(const string &s) {
    int n = sz(s);
    vector<int> pi(n);
    for(int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while(j && s[i] != s[j]) j = pi[j - 1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp(const string &s, const string &pat) {
    assert(!pat.empty());
    vector<int> pi = prefix_function(pat), ans;
    int j = 0;
    for(int i = 0; i < sz(s); i++) {
        while(j && s[i] != pat[j]) j = pi[j - 1];
        if(s[i] == pat[j]) j++;
        if(j == sz(pat)) {
            ans.pb(i - sz(pat) + 1);
            j = pi[j - 1];
        }
    }
    return ans;
}
