#include <iostream>
#include <vector>
using namespace std;

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define INSIDE 0
#define OUTSIDE 1

typedef struct {
	double x;
	double y;
} Point;

int InsidePolygon(vector<Point> polygon,int N,Point p)
{
	int counter = 0;
	int i;
	double xinters;
	Point p1,p2;
	
	p1 = polygon[0];
	for (i=1;i<=N;i++) {
		p2 = polygon[i % N];
		if (p.y > MIN(p1.y,p2.y)) {
			if (p.y <= MAX(p1.y,p2.y)) {
				if (p.x <= MAX(p1.x,p2.x)) {
					if (p1.y != p2.y) {
						xinters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
						if (p1.x == p2.x || p.x <= xinters)
							counter++;
					}
				}
			}
		}
		p1 = p2;
	}
	
	if (counter % 2 == 0)
		return(OUTSIDE);
	else
		return(INSIDE);
}

int main(int argc, char *argv[]) {
	
	int nP,nV;
	
	vector<Point> plantas, poligono;
	
	while(cin>>nP>>nV){
		
		Point aux={0,0};
		
		plantas.assign(nP,aux);
		
		for(int i=0;i<nP;i++) { 
			Point p;
			cin>>p.x>>p.y;
			plantas[i]=p;
		}
		
		poligono.assign(nV,aux);
		
		for(int i=0;i<nV;i++) { 
			Point p;
			cin>>p.x>>p.y;
			poligono[i]=p;
		}
		
		int contador=0;
		for(int i=0;i<nP;i++) { 
			if(InsidePolygon(poligono,nV,plantas[i]))
				contador+=i+1;
		}
		cout<<contador<<endl;
	}
	
	
	return 0;
}

