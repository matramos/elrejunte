/*Ejercicio Mice and Maze de la Guia 7*/
//  http://www.spoj.com/problems/MICEMAZE/
//  ACC


#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

struct Edge{
	int v;   		// nodo vecino
	int weight; 	// peso
};

class Graph_w{
private:
	vector<vector<Edge> > edges;  	// informacion de adyacencia
	int nedges;						   // numero de arcos en el grafo	
	vector<bool> processed;
	vector<bool> discovered;
	vector<int> parents;				// se utiliza para imprimir alguna solucion de la busqueda
	vector<int> distance;         // distancia optima al inicio despues de aplicar dijkstra 
	bool finished;						// se utiliza como corte de la busqueda en profundidad
	
public:
	Graph_w():nedges(0){}
	
	
	// Lee e inicializa el grafo. El grafo puede ser dirigido 
	// o no de acuerdo al parametro directed 
	void read(bool directed, int n_nodes);
	
	int dijkstra(int start, int exit);
	void prim(int start);
	void print();
	void print_path(int dest);
	void print_parents();
};


int main(){
	Graph_w g;
	int exit, time, nodes;
	int mices = 0;
	cin >> nodes >> exit >> time;
	
	g.read(true, nodes);
		
	
	
	for(int i = 0; i < nodes; i++){
		if ((g.dijkstra(i, exit)) <= time) mices++;
	}
	
	cout << endl << mices << endl;
	
	return 0;
}


void Graph_w::read(bool directed, int n_nodes){
	nedges = 0; 
	edges.clear();
	
	int n_edges, x, y; 
	
	cin >> n_edges;
	
	edges.resize(n_nodes);	
	
	for(int i = 0; i < n_edges; i++) {
		Edge e;
		
		cin >> x >> y >> e.weight;
		x -= 1;
		y -= 1;
		e.v = y;
		edges[x].push_back(e); 
		
		++nedges;
		
		if(directed == false){ // tener en cuenta si es un arco al mismo nodo, se puede preguntar x != y !
			e.v = x;
			edges[y].push_back(e); 
		}
	}		
}

int Graph_w::dijkstra(int start, int exit) {
	vector<bool> in_tree(edges.size(), false);
	
	exit -= 1;
	
	Edge current = {start, 0};
	
	parents.assign(edges.size(), -1);        
	distance.assign(edges.size(),  numeric_limits<int>::max());
	distance[start] = 0;
	
	while(!in_tree[current.v]){
		in_tree[current.v] = true;
		
		for(unsigned i = 0; i < edges[current.v].size(); i++) {
			Edge next = {edges[current.v][i].v, edges[current.v][i].weight};			
			
			if (distance[next.v] > (distance[current.v] + next.weight)) {
				distance[next.v] = distance[current.v] + next.weight;
				parents[next.v] = current.v;
			}
		}
		
		current.v = 0;
		current.weight = numeric_limits<int>::max();
		
		for(unsigned i = 1; i < edges.size(); i++){
			if(!in_tree[i] && current.weight > distance[i]){
				current.weight = distance[i];
				current.v 	   = i;
			}
		}
	}
	
	return distance[exit];
}

void Graph_w::prim(int start) {
	vector<bool> in_tree(edges.size(), false); 
	Edge current = {start, 0};
	
	parents.assign(edges.size(), -1);        
	distance.assign(edges.size(),  numeric_limits<int>::max());
	distance[start] = 0;
	
	while(!in_tree[current.v]){
		in_tree[current.v] = true;
		
		for(unsigned i = 0; i < edges[current.v].size(); i++) {
			Edge next = {edges[current.v][i].v, edges[current.v][i].weight};			
			
			if (distance[next.v] > next.weight && in_tree[next.v] == false) {
				distance[next.v] = next.weight;
				parents[next.v] = current.v;
			}
		}
		
		current.v = 0;
		current.weight = numeric_limits<int>::max();
		
		for(unsigned i = 1; i < edges.size(); i++){
			if(!in_tree[i] && current.weight > distance[i]){
				current.weight = distance[i];
				current.v 	   = i;
			}
		}
	}	
}

void Graph_w::print(){
	for (unsigned i = 0; i < edges.size(); i++) {
		cout << i << ": ";
		
		for (unsigned j = 0; j < edges[i].size(); j++)
			cout << edges[i][j].v << "(" << edges[i][j].weight << ")  ";
		
		cout << endl;
	}
}

void Graph_w::print_path(int dest){
	stack<int> s;
	int it = dest;
	
	while(it != -1){
		s.push(it);
		it = parents[it];
	}
	
	cout << "path: ";	
	
	while(!s.empty()){
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl << "minimum cost: " << distance[dest] << endl;
}

void Graph_w::print_parents(){
	for(int i = 0; i < parents.size(); i++){
		cout << i << ": "  << parents[i] << endl;
	}
}

