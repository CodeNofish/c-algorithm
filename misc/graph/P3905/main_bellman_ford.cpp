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

bool bellman_ford(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[root] = 0;
    parent[root] = -1;
    for (int k = 0; k < node_cnt - 1; k++) {
        // relax
        bool relaxed = false;
        for (int u = 1; u <= node_cnt; u++) {
            if (dist[u] == INF)continue;
            for (int i = head[u]; i; i = e[i].n) {
                int v = e[i].v, w = get_weight(i);
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    relaxed = true;
                }
            }
        }
        if (!relaxed)return true;
    }
    for (int u = 1; u <= node_cnt; u++) {
        if (dist[u] == INF)continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = get_weight(i);
            if (dist[v] > dist[u] + w)
                return false;
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
    bellman_ford(u, n);
    cout << dist[v];
}