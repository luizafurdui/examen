#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 101

int n, m;
int graph[MAX][MAX];  // Matrice de adiacență a grafului
int trgraph[MAX][MAX];  // Matricea transpusă a grafului
int stack[MAX], top = 0;  // Stivă pentru ordonare topologică
int visited[MAX];  // Vector de vizitare

// DFS pentru ordonare topologică
void dfsFirst(int v) {
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i])
            dfsFirst(i);
    }
    stack[top++] = v;  // Salvăm nodul în stivă după terminarea DFS
}

// Construim graful transpus
void transposeGraph() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            trgraph[j][i] = graph[i][j];  // Inversăm muchiile
}

// DFS pentru SCC
void dfsSecond(int v) {
    visited[v] = 1;
    printf("%d ", v);  // Afișăm nodul ca parte din SCC
    for (int i = 0; i < n; i++) {
        if (trgraph[v][i] && !visited[i])
            dfsSecond(i);
    }
}

// Algoritmul Kosaraju pentru SCC
void kosaraju() {
    int i;
    top = 0;  // Resetăm top-ul stivei

    // 1. DFS inițial pentru ordonare topologică
    for (i = 0; i < n; i++)
        visited[i] = 0;

    for (i = 0; i < n; i++)
        if (!visited[i])
            dfsFirst(i);

    // 2. Construim graful transpus
    transposeGraph();

    // 3. A doua DFS pentru SCC
    for (i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nComponentele tare conexe sunt:\n");
    while (top) {
        int v = stack[--top];  // Luăm nodurile din stivă
        if (!visited[v]) {
            dfsSecond(v);
            printf("\n");  // Nouă componentă tare conexă
        }
    }
}

int main() {
    int a, b;

    scanf_s("%d %d", &n, &m);

    // Inițializăm graful
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    // Citim muchiile
    printf("Introduceți cele %d muchii (format: nod1 nod2):\n", m);
    for (int i = 0; i < m; i++) {
        scanf_s("%d %d", &a, &b);
        graph[a][b] = 1;  // Graful este orientat
    }

    // Afișăm matricea de adiacență
    printf("\nMatricea de adiacență:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    // Rulăm algoritmul Kosaraju
    kosaraju();

    return 0;
}
