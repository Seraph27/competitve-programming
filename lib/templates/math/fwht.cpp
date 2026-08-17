// XOR transform, sz(a) must be a power of two.
void fwht(vector<int> &a, bool inv) {
    int n = sz(a);
    assert(n > 0 && (n & (n - 1)) == 0);
    for(int len = 1; len < n; len <<= 1) {
        for(int i = 0; i < n; i += len << 1) {
            for(int j = 0; j < len; j++) {
                int l = a[i + j], r = a[i + j + len];
                a[i + j] = l + r;
                a[i + j + len] = l - r;
                if(inv) {
                    a[i + j] /= 2;
                    a[i + j + len] /= 2;
                }
            }
        }
    }
}
