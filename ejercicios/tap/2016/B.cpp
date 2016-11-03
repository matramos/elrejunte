#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define INF 1000000000
struct point
{
	int x, y;
	point(int _x, int _y): x(_x), y(_y){}
};

vector<point> posiciones;
vector< vector<double> > matriz;



void calcular(){
	double dist;
	for (unsigned int i = 0; i < posiciones.size(); ++i)
	{
		for (unsigned int j = i+1; j < posiciones.size(); ++j)
		{
			dist = hypot(posiciones[i].x - posiciones[j].x, posiciones[i].y - posiciones[j].y);
			matriz[i][j] = dist;
			matriz[j][i] = dist;
		}
	}
}

int main()
{
	int nodos, ent, sal;

	int x, y;

    freopen("input","r",stdin);
    freopen("output","w",stdout);

	cin>>nodos>>ent>>sal;

	for (int i = 0; i < nodos; ++i)
	{
		cin>>x>>y;
		posiciones.push_back(point(x,y));
	}
	
    
    calcular();




    return 0;
}