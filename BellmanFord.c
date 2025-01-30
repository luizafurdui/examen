
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define infinit INT_MAX
typedef struct {
	int u, v, w; 
}edge;
void bellmanFord(int V, int E ,edge edges[], int src) {
	int dist[101];

	for (int i = 0; i < V; i++)
		dist[i] = infinit; 
	dist[src] = 0; 
	//parcurg de v-1 ori 
	for (int i = 1; i < V; i++)
	{
		for (int j = 0; j < E; j++)
		{
			int u = edges[j].u; 
			int v = edges[j].v; 
			int weight = edges[j].w; 

			if (dist[u] != infinit && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight; 
			}

		}
	}

	//detectatea ciclurilor negative
	for (int j = 0; j < E; j++)
	{
		int u = edges[j].u; 
		int v = edges[j].v; 
		int weight = edges[j].w; 
		if (dist[u] != infinit && dist[u] + weight < dist[v]) //daca inca se modifica vectorul dist inseamna ca am un cilcu de cost negativ
		{
			printf("Graful contine un ciclu de cost negativ\n");
			return;
		}
	}


	// Afișare rezultate
	printf("Distantele minime de la sursa %d:\n", src);
	for (int i = 0; i < V; i++) {
		if (dist[i] == infinit)
			printf("Nodul %d: INF\n", i);
		else
			printf("Nodul %d: %d\n", i, dist[i]);
	}

}
int main()
{
	int V = 5;  //noduri; 
	int E = 4; //noduri 

	edge edges[] = {
		{1, 2, 4},  
		{1, 4, 5},   
		{4, 3, 3},  
		{3, 2, -10}  
	
	};
	int src = 1; //nodul sursa
	bellmanFord(V,E,edges,src); 

	return 0; 
}

