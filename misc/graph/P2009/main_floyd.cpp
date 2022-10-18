#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define INF 0x7fffffff
#define N (20+4)
#define M (N*N*2+4)

struct edge {
    int v, w, n;
};
edge e[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    for (int i = head[u]; i; i = e[i].n) {  // 补丁
        if (e[i].v == v) {
            e[i].w = max(e[i].w, w);
            return;
        }
    }
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    head[u] = edge_cnt;
}

int get_val(int u, int v) {
    for (int i = head[u]; i; i = e[i].n) {
        int w = e[i].w;
        if (v == e[i].v) {
            return w;
        }
    }
    return -1;
}

int dist[N][N];
int parent[N][N];

void floyd(int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        for (int j = 1; j <= node_cnt; j++) {
            dist[i][j] = INF;
            parent[i][j] = -1;
        }
        dist[i][i] = 0;
    }
    for (int u = 1; u <= node_cnt; u++) {
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (u == v) continue;
            dist[u][v] = w;
            parent[u][v] = u;
        }
    }
    for (int k = 1; k <= node_cnt; k++) {
        for (int i = 1; i <= node_cnt; i++) {
            for (int j = 1; j <= node_cnt; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[i][k];
                }
            }
        }
    }
}

int
main() {
    int n, m;
    int v;
    char x, y;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v;
        add_edge(i, 1 + i % n, v);
        add_edge(1 + i % n, i, v);
    }
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> v;
        add_edge(x - 'A' + 1, y - 'A' + 1, v);
        add_edge(y - 'A' + 1, x - 'A' + 1, v);
    }
    cin >> x >> y;
    if (x == y) {   // 补丁
        cout << get_val(x - 'A' + 1, y - 'A' + 1);
        return 0;
    }
    floyd(n);
    cout << dist[x - 'A' + 1][y - 'A' + 1];
}