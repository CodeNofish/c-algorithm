#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define INF 0x7fffffff
#define N (1500+4)
#define M (50000+4)
struct edge {
    int v, w, n;
};
edge e[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    for (int i = head[u]; i; i = e[i].n) {
        if (v == e[i].v) {
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

int dist[N], parent[N];

bool bellman_ford(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = -INF;
        parent[i] = -1;
    }
    dist[root] = 0;
    // relax n-1 times
    for (int k = 0; k < node_cnt - 1; k++) {
        bool relaxed = false;
        for (int u = 1; u <= node_cnt; u++) {
            if (dist[u] == -INF) continue;
            for (int i = head[u]; i; i = e[i].n) {
                int v = e[i].v, w = e[i].w;
                if (dist[v] < dist[u] + w) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    relaxed = true;
                }
            }
        }
        if (!relaxed) return true;
    }
    for (int u = 1; u <= node_cnt; u++) {
        if (dist[u] == -INF) continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] < dist[u] + w)
                return false;
        }
    }
    return true;
}

int
main() {
    // 带权有向无环图
    int n, m;
    int u, v, w;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        // 有负边 重边
        add_edge(u, v, w);
    }
    bellman_ford(1, n);
    cout << (dist[n] == -INF ? -1 : dist[n]);
}