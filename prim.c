// Algoritmul lui Prim
#include <stdio.h>
#include <limits.h>

#define I 123231 // Definim infinitul


int n = 7;
int cost[8][8] = {
    {I, I, I, I, I, I, I, I},
    {I, I, 25, I, I, I, 5, I},
    {I, 25, I, 12, I, I, I, 10},
    {I, I, 12, I, 8, I, I, I},
    {I, I, I, 8, I, 16, I, 14},
    {I, I, I, I, 16, I, 20, 18},
    {I, 5, I, I, I, 20, I, I},
    {I, I, 10, I, 14, 18, I, I}
};

int near[8]; // Vector pentru nodurile cele mai apropiate
int t[2][6]; // Matrice pentru muchiile MST

int main() {
    int i, j, u, v, min = I;
    

    // 1️⃣ Găsim prima muchie minimă din matricea de costuri
    for (i = 1; i < n; i++) {
        for (j = i; j < n; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                u = i;
                v = j;
            }
        }
    }

    // 2️⃣ Adăugăm prima muchie la MST
    t[0][0] = u;
    t[1][0] = v;

    // Marcăm nodurile adăugate în MST
    near[u] = near[v] = 0;

    // 3️⃣ Inițializăm vectorul near[]
    for (i = 1; i < n; i++) {
        if (near[i] != 0) { // Dacă nodul nu e în MST
            if (cost[i][u] < cost[i][v])
                near[i] = u;
            else
                near[i] = v;
        }
    }

    // 4️⃣ Construim MST iterativ
    for (i = 1; i < n - 1; i++) {
        min = I;
        int k;

        // Găsim nodul cel mai apropiat de MST
        for (j = 1; j < n; j++) {
            if (near[j] != 0 && cost[j][near[j]] < min) {
                min = cost[j][near[j]];
                k = j;
            }
        }

        // Adăugăm muchia la MST
        t[0][i] = k;
        t[1][i] = near[k];
        near[k] = 0; // Marcam nodul k ca parte din MST

        // Actualizăm near[]
        for (j = 1; j < n; j++) {
            if (near[j] != 0 && cost[j][k] < cost[j][near[j]]) {
                near[j] = k;
            }
        }
    }

    // 5️⃣ Afișăm MST
    printf("Muchiile arborelui de acoperire minim sunt:\n");
    for (i = 0; i < n - 1; i++) {
        printf("(%d, %d)\n", t[0][i], t[1][i]);
    }

    return 0;
}
