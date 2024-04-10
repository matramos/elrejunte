struct ST {
  int sz;
  vector<Elem> t;
  vector<Alt> dirty; // Alt and Elem could be diff types
  ST(int n) {
    sz = 1 << (32 - __builtin_clz(n));
    t = vector<Elem>(2 * sz, neutro);
    dirty = vector<Alt>(2 * sz, neutro2);
  }
  Elem& operator[](int p) { return t[sz + p]; }
  void updall() {dforn(i,sz) t[i] = oper(t[2*i], t[2*i+1]);}
  void push(int n, int a, int b) {//push dirt to child nodes
    if (dirty[n] != neutro2) {    //n = node of range [a,b)
      t[n] += dirty[n] * (b - a); //CHANGE for your problem
      if (n < sz) {
        dirty[2*n] += dirty[n];   // CHANGE for your problem
        dirty[2*n+1] += dirty[n]; // CHANGE for your problem
      }
      dirty[n] = neutro2;
    }
  }
  Elem get(int i, int j, int n, int a, int b) {  // O(lgn)
    if (j <= a || b <= i) return neutro;
    push(n, a, b); // adjust value before using it
    if (i <= a && b <= j) return t[n];  // n = node of [a,b)
    int c = (a + b) / 2;
    return oper(get(i,j, 2*n, a, c), get(i,j, 2*n+1, c, b));
  }
  Elem get(int i, int j) { return get(i, j, 1, 0, sz); }
  void update(Alt val, int i, int j, int n, int a, int b) {
    push(n, a, b);
    if (j <= a || b <= i) return;
    if (i <= a && b <= j) {
      dirty[n] += val;  // CHANGE for your problem
      push(n, a, b);
      return;
    }
    int c = (a + b) / 2;
    update(val,i,j, 2*n, a,c), update(val,i,j, 2*n+1, c,b);
    t[n] = oper(t[2 * n], t[2 * n + 1]);
  }
  void update(Alt val, int i,int j){update(val,i,j,1,0,sz);}
};  // Use: operacion, neutros, Alt, Elem, uso de dirty
