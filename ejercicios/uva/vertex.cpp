//  http://uva.onlinejudge.org/external/2/280.html
/*Ejercicio Vertex de la Guía 6*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph{
	private:
		vector<vector<int> > edges;  	// informacion de adyacencia
		int nedges;						   // numero de arcos en el grafo
		
		vector<bool> processed;
		vector<bool> discovered;
		vector<int> parents;				// se utiliza para imprimir alguna solucion de la busqueda
		bool finished;						// se utiliza como corte de la búsqueda en profundidad

	public:
		Graph():nedges(0){}

		/*
		 * Lee e inicializa el grafo. El grafo puede ser dirigido 
		 * o no de acuerdo al parametro directed 
		 */ void read(bool directed, int vertices);
		
		/*
		 * Imprime el grafo
		 */ void print();

		/*
		 * Busqueda en amplitud
		 */ void bfs(int start);
		 
		/*
		 * Busqueda en profundidad
		 */ void dfs(int start);
		 
		/*
		 * Procesar nodo
		 * Para la busqueda dfs, modificar finished segun el problema
		 */ void process_node(int v);

		/*
		 * Procesar arco
		 * Para la busqueda dfs, modificar finished segun el problema
		 */ void process_edge(int x, int y);

		/*
		 * Decidir si un arco es válido
		 * Para la busqueda dfs, modificar finished segun el problema
		 */ bool valid_edge(int node, int edge);

		/*
		 * Imprime la ruta encontrada por la busqueda. 
		 * Modificar el formato de impresion de acuerdo al problema
		 */ void print_path(int start, int end);
		
		/*
		 * Devuelve true si el grafo es DAG (Grafo Aciclico Dirigido), y
		 * ademas inicializa el vector sorted pasado como parametro.
		 * Devuelve false si el grafo no es DAG, sorted queda vacio.
		 */ bool topological_sort(vector<int> &sorted);

		/*
		 * Devuelve el numero de componentes conectados en el grafo
		 */ int connected_components();
};

int main(){
	Graph g;
	int vertices, consultas, vertex;
	
	cin >> vertices;
	while(vertices !=0){
		g.read(true, vertices);
		g.print();
		cin >> consultas;
		for (int c=1; c<=consultas; c++){
			cin >> vertex;
			g.bfs(vertex-1);
		}
		
		cin >> vertices;
	}
	
/*	g.print();

	g.bfs(0);*/
	//cout << "componentes conectadas : " << g.connected_components() << endl;
	//cout << "para topological sort: usar dfs() " << endl;
	 

/*
	g.print_path(0, 3);
	g.print_path(0, 2);
	g.print_path(0, 1);*/
	return 0;
}

void Graph::read(bool directed, int vertices){
	// initialize graph
	nedges = 0; 
	edges.clear();

	int n_nodes,nodo, destino; 

	n_nodes = vertices;
	
	edges.resize(n_nodes);	
	
	cin >> nodo;
	while(nodo!=0) {
		cin >> destino;
		while (destino!=0){
			edges[nodo-1].push_back(destino-1); 
			++nedges;
			
			cin >> destino;
		}
  		/*if(directed == false) // tener en cuenta si es un arco al mismo nodo, se puede preguntar x != y !
			edges[y].push_back(x); */
		
		cin >> nodo;
	}		
}

// BREADTH FIRST SEARCH
void Graph::bfs(int start){
   queue<int> q;
   int nodescubiertos=0;
   
   // inicializar datos	
	processed.assign( edges.size(), false);
	discovered.assign( edges.size(), false);
	parents.assign(edges.size(), -1);
	                         
	q.push(start);   		
   //discovered[start] = true; 		// marcar como descubierto
        
	while (!q.empty()) { 			// mientras la cola no este vacia
		int v = q.front();     		// obtener un elemento de la cola
		q.pop();
      process_node(v);   			// procesar el vertice
      processed[v] = true; 		// marcar como procesado 
                
		for (unsigned i = 0; i < edges[v].size(); i++) {
			if( valid_edge(v, edges[v][i]) ){
				if(!discovered[edges[v][i]]) {
					q.push(edges[v][i]);
					discovered[edges[v][i]] = true;
               parents[edges[v][i]] = v;
            }
            if (!processed[edges[v][i]])
	            process_edge(v, edges[v][i]);
         }
		}
	}
	
	
	for(unsigned i=0; i<discovered.size(); i++){
		if (discovered[i] == false) nodescubiertos++;
	}
	cout << nodescubiertos << " ";
	
	for(unsigned i=0; i<discovered.size(); i++){
		if (discovered[i] == false) cout << i+1 << " ";
	}
	cout << endl;
}

void Graph::process_node(int v){
	//cout << "processed node " << v << endl;
}

void Graph::process_edge(int x, int y){
	//cout << "processed edge (" << x << ", " << y << ")" << endl;
}

bool Graph::valid_edge(int node, int edge){
	return true;
}

void Graph::print_path(int start, int end){
	if( start == end || end == -1){
		if(end == -1) 
			cout << "error ";
			
		cout << endl << start;
	} else {
		print_path(start, parents[end]);
		cout << " " << end; 
  }
}

// DEPTH FIRST SEARCH
void Graph::dfs(int start){
	stack<int> s;
	finished = false;
   
   // inicializar datos	
	processed.assign( edges.size(), false);
	discovered.assign( edges.size(), false);
	parents.assign(edges.size(), -1);
	                         
	s.push(start);   		
    discovered[start] = true; 		// marcar como descubierto
        
	while (!s.empty()) { 			// mientras la pila no este vacia
	  int v = s.top(); 				// obtener un elemento de la pila
	  s.pop();
      process_node(v); 				// procesar el vertice
      
      if(finished) return;
                
		for (unsigned i = 0; i < edges[v].size(); i++) {
			if( valid_edge(v, edges[v][i]) ){
				if(!discovered[edges[v][i]]) {
					s.push(edges[v][i]);
					discovered[edges[v][i]] = true;
               parents[edges[v][i]] = v;
            }
            if (!processed[edges[v][i]])
	            process_edge(v, edges[v][i]);
         }
		}
		processed[v] = true; 		// marcar como procesado 
	}
}

bool Graph::topological_sort(vector<int> &sorted){
	vector<int> in_degree(edges.size());
	queue<int> zero_in;
	int current, next;

	// Inicializamos el vector de grados entrantes
	in_degree.assign(edges.size(), 0);
	for(unsigned i = 0; i < edges.size(); i++){
		for(unsigned j = 0; j < edges[i].size(); j++){
			in_degree[ edges[i][j] ]++;
		}
	}
	// *******************************************
		    
	for(unsigned i = 0; i < edges.size(); i++){
	   if (in_degree[i] == 0) 
	   	zero_in.push(i);
	}
	
	while(!zero_in.empty()){
	   current = zero_in.front();
	   zero_in.pop();
	   sorted.push_back(current);
	   
	   for(unsigned i = 0; i < edges[current].size(); i++){
		   next = edges[current][i];
		   in_degree[next]--;
		   if(in_degree[next] == 0)
		   	zero_in.push(next);
	   }
	}
	
	if(sorted.size() != edges.size()){
		sorted.clear();
		return false;
	}
	return true;
}

int Graph::connected_components(){
	int connected_count = 0;
   
   discovered.assign(edges.size(), false);
   
	for(unsigned i = 0; i < discovered.size(); i++){
		if(discovered[i]) continue;
		
		connected_count++;
		// BFS
	   queue<int> q;
		q.push(i); 
		discovered[i] = true; 		// marcar como descubierto
			  
		while (!q.empty()) { 			// mientras la cola no este vacia
			int v = q.front();     		// obtener un elemento de la cola
			q.pop();
			          
			for (unsigned i = 0; i < edges[v].size(); i++) {
				if(!discovered[edges[v][i]]) {
					q.push(edges[v][i]);
					discovered[edges[v][i]] = true;
		      }
			}
		}
		// end BFS
	}
	return connected_count;
}

void Graph::print(){
	for (unsigned i = 0; i < edges.size(); i++) {
		cout << i << ": ";

		for (unsigned j = 0; j < edges[i].size(); j++)
			cout << edges[i][j] << " ";

		cout << endl;
	}
}
