#include <iostream>
#include <algorithm>

using namespace std;
#define N 2504
#define M 6204
#define INF 0x7fffffff

struct edge {
    int v, w, n;
};
edge e[M * 2];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    for (int i = head[u]; i; i = e[i].n) {
        if (v == e[i].v) {
            e[i].w = min(e[i].w, w);
            return;
        }
    }
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    head[u] = edge_cnt;
}

int n, m, s, t;

int dist[N][N];
int parent[N][N];

int floyd() {
    // init
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INF;
            parent[i][j] = -1;
        }
        dist[i][i] = 0;
    }
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            dist[u][v] = w;
            parent[u][v] = u;
        }
    }
    // use k to relax i->j
    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                // u->k->v  better than  u->v
                if (dist[u][k] == INF || dist[k][v] == INF)
                    continue;
                if (dist[u][v] > dist[u][k] + dist[k][v]) {
                    dist[u][v] = dist[u][k] + dist[k][v];
                    parent[u][v] = parent[k][v];
                }
            }
        }
    }
}

// n^3 超时哦
int
main() {
    int u, v, w;
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    floyd();
    cout << dist[s][t];
}