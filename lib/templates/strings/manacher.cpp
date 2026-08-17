// d1[i]: odd radius including i, d2[i]: even radius centered before i.
pair<vector<int>, vector<int>> manacher(const string &s) {
    int n = sz(s);
    vector<int> d1(n), d2(n);
    for(int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
        while(i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if(i + k > r) l = i - k, r = i + k;
    }
    for(int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while(i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if(i + k > r) l = i - k - 1, r = i + k;
    }
    return {d1, d2};
}
