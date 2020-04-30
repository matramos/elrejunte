typedef int tipo;
tipo oper(const tipo &a, const tipo &b){
    return a+b;
}
struct node{
	tipo v; node *l, *r;
	node(tipo v) : v(v), l(NULL), r(NULL) {}
    node(node *l, node *r) : l(l), r(r) {
        if(!l) v = r->v;
        else if(!r) v = l->v;
        else v = oper(l->v, r->v);
    }
};
node *build(tipo *a, int tl, int tr) {//build a partir de un arreglo
	if(tl+1 == tr) return new node(a[tl]);
	int tm = (tl+tr)>>1;
	return new node(build(a, tl, tm), build(a, tm, tr));
}
node *update(int pos, int new_val, node *t, int tl, int tr) {
	if(tl+1 == tr) return new node(new_val);
	int tm = (tl+tr)>>1;
	if(pos < tm) return new node(update(pos, new_val, t->l, tl, tm), t->r);
	else return new node(t->l, update(pos, new_val, t->r, tm, tr));
}
tipo get(int l, int r, node *t, int tl, int tr) {
    if(l==tl && tr==r) return t->v;
	int tm = (tl+tr)>>1;
    if(r <= tm) return get(l, r, t->l, tl, tm);
    else if(l >= tm) return get(l, r, t->r, tm, tr);
	return oper(get(l, tm, t->l, tl, tm), get(tm, r, t->r, tm, tr));
}
//node t represents range [tl, tr). For roots alway use tl = 0, tr = size