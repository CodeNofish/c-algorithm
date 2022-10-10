#include <iostream>
#include <algorithm>

using namespace std;
#define N (100+4)
#define M N*N
#define INF 0x7fffffff
struct edge {
    int v, w, n;
    bool broken;
};
edge e[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    e[edge_cnt].broken = false;
    head[u] = edge_cnt;
}

void add_broken(int u, int v) {
    for (int i = head[u]; i; i = e[i].n)
        if (v == e[i].v)
            e[i].broken = true;
}

int get_weight(int idx) {
    if (e[idx].broken)
        return e[idx].w;
    return 0;
}

int dist[N][N];
int parent[N][N];

bool floyd(int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        for (int j = 1; j <= node_cnt; j++) {
            dist[i][j] = INF;
            parent[i][j] = -1;
        }
        dist[i][i] = 0;
    }
    // init by egdes
    for (int u = 1; u <= node_cnt; u++) {
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = get_weight(i);
            dist[u][v] = w;
            parent[u][v] = u;
        }
    }
    // use node k relax dist
    for (int k = 1; k <= node_cnt; k++) {
        for (int u = 1; u <= node_cnt; u++) {
            for (int v = 1; v <= node_cnt; v++) {
                if (dist[u][k] == INF || dist[k][v] == INF)
                    continue;
                // 从k走更近
                if (dist[u][v] > dist[u][k] + dist[k][v]) {
                    dist[u][v] = dist[u][k] + dist[k][v];
                    parent[u][v] = parent[k][v];
                }
            }
        }
    }
    return true;
}

int
main() {
    int n, m, d;
    int u, v, w;
    // 把好的路 视作边权为0的 求最短路径
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    cin >> d;
    for (int i = 0; i < d; i++) {
        cin >> u >> v;
        add_broken(u, v);
        add_broken(v, u);
    }
    cin >> u >> v;
    floyd(n);
    cout << dist[u][v];
}