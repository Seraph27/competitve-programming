template<int CAP>
struct DLX {
  int n, m, tot, ans;
  int L[CAP], R[CAP], U[CAP], D[CAP], col[CAP], row[CAP];
  vector<int> firstRow, sizCol, stk;

  // Rows and columns are 1-indexed; CAP includes column headers and all 1s.
  void build(int r, int c) {
    n = r; m = c; tot = m; ans = 0;
    for (int i = 0; i <= m; ++i) { L[i] = i - 1; R[i] = i + 1; U[i] = D[i] = i; }
    L[0] = m; R[m] = 0;
    firstRow.assign(n + 1, 0);
    sizCol.assign(m + 1, 0);
    stk.assign(n + 1, 0);
  }

  void insert(int r, int c) {
      assert(tot + 1 < CAP);
      ++tot;
    col[tot] = c; row[tot] = r; ++sizCol[c];
    D[tot] = D[c]; U[D[c]] = tot; U[tot] = c; D[c] = tot;
    if (!firstRow[r]) firstRow[r] = L[tot] = R[tot] = tot;
    else { R[tot] = R[firstRow[r]]; L[R[firstRow[r]]] = tot; L[tot] = firstRow[r]; R[firstRow[r]] = tot; }
  }

  void remove(int c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i])
      for (int j = R[i]; j != i; j = R[j]) { U[D[j]] = U[j]; D[U[j]] = D[j]; --sizCol[col[j]]; }
  }

  void recover(int c) {
    for (int i = U[c]; i != c; i = U[i])
      for (int j = L[i]; j != i; j = L[j]) { ++sizCol[col[j]]; U[D[j]] = j; D[U[j]] = j; }
    L[R[c]] = c; R[L[c]] = c;
  }

  bool dance(int dep = 0) {
    if (R[0] == 0) { ans = dep; return true; }
    int c = R[0];
    for (int j = R[0]; j != 0; j = R[j]) if (sizCol[j] < sizCol[c]) c = j;
    remove(c);
    for (int i = D[c]; i != c; i = D[i]) {
      stk[dep] = row[i];
      for (int j = R[i]; j != i; j = R[j]) remove(col[j]);
      if (dance(dep + 1)) return true;
      for (int j = L[i]; j != i; j = L[j]) recover(col[j]);
    }
    recover(c);
    return false;
  }
};
