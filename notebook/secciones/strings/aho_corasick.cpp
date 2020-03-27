struct Trie{
	map<char, Trie> next;
	Trie* tran[256];//transiciones del automata
	int idhoja, szhoja;//id de la hoja o 0 si no lo es
	//link lleva al sufijo mas largo, nxthoja lleva al mas largo pero que es hoja
	Trie *padre, *link, *nxthoja;
	char pch;//caracter que conecta con padre
	//Trie(): tran(),  idhoja(), padre(), link() {}
	//comento linea de arriba porque me daba errores usarla.
	void insert(const string &s, int id=1, int p=0) //id>0!!!
	{
		if(p<sz(s))
		{
			Trie &ch=next[s[p]];
			tran[(int)s[p]]=&ch;
			ch.padre=this, ch.pch=s[p];
			ch.insert(s, id, p+1);
		}
		else idhoja=id, szhoja=sz(s);
	}
	Trie* get_link()
	{
		if(!link)
		{
			if(!padre) link=this;//es la raiz
			else if(!padre->padre) link=padre;//hijo de la raiz
			else link=padre->get_link()->get_tran(pch);
		}
		return link;
	}
	Trie* get_tran(int c)
	{
		if(!tran[c]) tran[c] = !padre? this : this->get_link()->get_tran(c);
		return tran[c];
	}
	Trie *get_nxthoja()
	{
		if(!nxthoja) nxthoja = get_link()->idhoja? link : link->nxthoja;
		return nxthoja;
	}
	void print(int p)
	{
		if(idhoja) cout << "found " << idhoja << "  at position " << p-szhoja << endl;
		if(get_nxthoja()) get_nxthoja()->print(p);
	}
	void matching(const string &s, int p=0) //O(|s| + tamanio palabras)
	{
		print(p); if(p<sz(s)) get_tran(s[p])->matching(s, p+1);
	}
};
