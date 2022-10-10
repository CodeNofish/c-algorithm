#include <iostream>
#include <algorithm>

using namespace std;
#define N (100+4)
#define M N*N
#define INF 0x7fffffff
struct edge {
    int v, w, n;
};
edge e[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    head[u] = edge_cnt;
}

int dist[N][N];
int parent[N][N];

void floyd(int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        for (int j = 1; j <= node_cnt; j++) {
            dist[i][j] = INF;
            parent[i][j] = i;
        }
        dist[i][i] = 0;
    }
    for (int u = 1; u <= node_cnt; u++) {
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            dist[u][v] = w;
            parent[u][v] = u;
        }
    }
    for (int k = 1; k <= node_cnt; k++) {
        for (int u = 1; u <= node_cnt; u++) {
            for (int v = 1; v <= node_cnt; v++) {
                if (dist[u][k] == INF || dist[k][v] == INF) continue;
                if (dist[u][v] > dist[u][k] + dist[k][v]) {
                    dist[u][v] = dist[u][k] + dist[k][v];
                    parent[u][v] = parent[k][v];
                }
            }
        }
    }
}

int
main() {
    int n, a, b;
    int k, v;
    cin >> n >> a >> b;
    for (int u = 1; u <= n; u++) {
        bool first = true;
        cin >> k;
        while (k--) {
            cin >> v;
            if (first) {
                add_edge(u, v, 0);
                first = false;
            }
            else {
                add_edge(u, v, 1);
            }
        }
    }
    floyd(n);
    cout << (dist[a][b] == INF ? -1 : dist[a][b]);
}