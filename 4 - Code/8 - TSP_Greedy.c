#include <stdio.h>

#define MAX 200

/* ---------- DATA STRUCTURE ---------- */
typedef struct {
    int u, v;
    float w;
} Edge;

typedef struct {
    int n, m;
    Edge edges[MAX * MAX];
} Graph;

int parent[MAX], deg[MAX]; // deg = degree (bậc) đỉnh
Edge PA[MAX];

/* ---------- GRAPH FUNCTIONS ---------- */
void init_graph(Graph* G, int n) {
    G->n = n;
    G->m = 0;
}
void add_edge(Graph* G, int u, int v, float w) { // base-0
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m++;
}
void swap_edge(Edge* a, Edge* b) {
    Edge t = *a;
    *a = *b;
    *b = t;
}

/* ---------- READ & PRINT ---------- */
void ReadFromFile(char* filename, Graph* G) {
    freopen(filename, "r", stdin);
    int n;
    scanf("%d", &n);
    init_graph(G, n);
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++) {
            float w;
            scanf("%f", &w);
            add_edge(G, u, v, w);
        }
    fclose(stdin);
}
void PrintEdgeList(Edge PA[], int k, int sumFlag) {
    float sum = 0;
    for (int e = 0; e < k; e++) {
        printf("%2d %c%c = %6.2f\n", e + 1, PA[e].u + 'a', PA[e].v + 'a', PA[e].w);
        if (sumFlag) sum += PA[e].w;
    }
    if (sumFlag) printf("Tong do dai cac canh = %.2f\n", sum);
}

/* ---------- UNION-FIND ---------- */
void init_forest(int n) {
    for (int i = 0; i < n; i++) parent[i] = i;
}
int find_root(int u) {
    while (parent[u] != u) u = parent[u];
    return u;
}
void unite(int r1, int r2) {
    parent[r2] = r1;
}

/* ---------- CHECK BẬC >= 3 ---------- */
int will_over_degree(int u, int v) {
    return (deg[u] + 1 > 2 || deg[v] + 1 > 2);
}

/* ---------- GREEDY TSP ---------- */
void TSP_Greedy(Graph* G) {
    init_forest(G->n);
    for (int i = 0; i < G->n; i++) deg[i] = 0;

    // 1. Sort edges by weight (bubble)
    for (int i = 0; i < G->m - 1; i++)
        for (int j = G->m - 1; j > i; j--)
            if (G->edges[j].w < G->edges[j - 1].w)
                swap_edge(&G->edges[j], &G->edges[j - 1]);

    // 2. Build partial tour (n-1 edges)
    int k = 0;
    for (int i = 0; i < G->m && k < G->n - 1; i++) {
        int u = G->edges[i].u;
        int v = G->edges[i].v;
        int r1 = find_root(u);
        int r2 = find_root(v);

        if (r1 != r2 && !will_over_degree(u, v)) {
            PA[k++] = G->edges[i];
            unite(r1, r2);
            deg[u]++; deg[v]++;
        }
    }

    // 3. Add last edge that closes the cycle
    for (int i = 0; i < G->m; i++) {
        int u = G->edges[i].u;
        int v = G->edges[i].v;
        if (!will_over_degree(u, v) && find_root(u) == find_root(v)) {
            PA[k++] = G->edges[i];
            break;
        }
    }

    PrintEdgeList(PA, k, 1);
}

/* ---------- MAIN ---------- */
int main() {
    Graph G;
    ReadFromFile("D:\\CODE C\\InputAlgo\\TSP.txt", &G);

    printf("Danh sach canh cua do thi:\n");
    PrintEdgeList(G.edges, G.m, 0);

    printf("\nPHUONG AN TSP:\n");
    TSP_Greedy(&G);

    return 0;
}
