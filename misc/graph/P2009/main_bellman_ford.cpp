#include <iostream>
#include <algorithm>
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
        bool relaxed = false;
        for (int u = 1; u <= node_cnt; u++) {
            if (dist[u] == INF) continue;
            for (int i = head[u]; i; i = e[i].n) {
                int v = e[i].v, w = e[i].w;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    relaxed = true;
                }
            }
        }
        if (!relaxed) return true;
    }
    for (int u = 1; u <= node_cnt; u++) {
        if (dist[u] == INF) continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] > dist[u] + w) {
                return false;
            }
        }
    }
    return true;
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
    bellman_ford(x - 'A' + 1, n);
    cout << dist[y - 'A' + 1];
}