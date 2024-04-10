struct ST { // Compressed segtree, works for any range
  ST *lc, *rc; tipo val; int L, R;
  ST(int l, int r, tipo x = neutro) { 
    lc = rc = nullptr; L = l, R = r, val = x;
  }
  ST(int l, int r, ST* lp, ST* rp) {
    if (lp != nullptr && rp != nullptr && lp->L > rp->L)
      swap(lp, rp);
    lc = lp, rc = rp, L = l, R = r;
    val = oper(lp==nullptr ? neutro : lp->val,
               rp==nullptr ? neutro : rp->val);
  }
  // O(log(R-L)), parameter 'isnew' only needed when persist
  // return ST* for persistent
  void set(int p, tipo x, bool isnew = false) {
    // if(!isnew) {                          // for persist
    //   ST* newnode = new ST(L, R, lc, rc); // for persist
    //   return newnode->set(p, x, true);    // for persist
    // }                                     // for persist
    if (L + 1 == R) {
      val = x;
      return;  // 'return this;' for persistent
    }
    int m = (L + R) / 2;
    ST** c = p < m ? &lc : &rc;
    if (!*c) *c = new ST(p, p + 1, x);
    else if ((*c)->L <= p && p < (*c)->R) {
      // *c = (*c)->set(p,x); // for persist
      (*c)->set(p, x);        // NOT persist
    } else {
      int l = L, r = R;
      while ((p < m) == ((*c)->L < m)) {
        if (p < m) r = m; else l = m;
        m = (l + r) / 2;
      }
      *c = new ST(l, r, *c, new ST(p, p + 1, x));
    }
    val=oper(lc ? lc->val : neutro, rc ? rc->val : neutro);
    // return this; // for persistent
  }
  tipo get(int ql, int qr) {  // O(log(R-L))
    if (qr <= L || R <= ql) return neutro;
    if (ql <= L && R <= qr) return val;
    return oper(lc ? lc->get(ql, qr) : neutro,
                rc ? rc->get(ql, qr) : neutro);
  }
}; // Usage: 1- RMQ st(MIN_INDEX, MAX_INDEX) 2- normally use
