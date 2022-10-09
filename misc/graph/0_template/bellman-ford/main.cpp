#include <iostream>
#include <algorithm>

using namespace std;
#define N 2504
#define M 6204
#define INF 0x7fffffff

struct edge {
    int u, v, w, n;
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
    e[edge_cnt].u = u;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    head[u] = edge_cnt;
}

int n, m, s, t;

int dist[N];
int parent[N];

bool bellman_ford(int root) {
    // init
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
//    for (int i = head[root]; i; i = e[i].n) {
//        int v = e[i].v, w = e[i].w;
//        dist[v] = w;
//        parent[v] = root;
//    }
    dist[root] = 0;
    // relaxed n-1 times
    for (int k = 1; k <= n - 1; k++) {
        int relaxed = false;
        for (int i = 1; i <= edge_cnt; i++) {
            // root->u->v  better than  root->v
            int u = e[i].u, v = e[i].v, w = e[i].w;
            if (dist[u] == INF) continue;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                relaxed = true;
            }
        }
        if (!relaxed) return true;
    }
    // test n
    for (int i = 1; i <= edge_cnt; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (dist[v] > dist[u] + w) {
            return false;
        }
    }
    return true;
}

int
main() {
    int u, v, w;
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    bellman_ford(s);
    cout << dist[t];
}