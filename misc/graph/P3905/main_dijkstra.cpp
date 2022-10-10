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

int dist[N];
int parent[N];
bool inU[N];

bool dijkstra(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
        parent[i] = -1;
        inU[i] = false;
    }
    dist[root] = 0;

    for (int k = 1; k <= node_cnt; k++) {
        // find min dist
        int min = INF, u = -1;
        for (int i = 1; i <= node_cnt; i++) {
            if (inU[i]) continue;
            if (min > dist[i]) {
                min = dist[i];
                u = i;
            }
        }
        if (u == -1)break;
        inU[u] = true;
        if (dist[u] == INF) continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = get_weight(i);
            if (inU[v]) continue;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
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
    dijkstra(u, n);
    cout << dist[v];
}