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

int dist[N];
int parent[N];

bool bellman_ford(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[root] = 0;
    for (int k = 1; k <= node_cnt - 1; k++) {
        bool relaxed = false;
        for (int u = 1; u <= node_cnt; u++) {
            if (dist[u] == INF)continue;
            for (int i = head[u]; i; i = e[i].n) {
                int v = e[i].v, w = e[i].w;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    relaxed = true;
                }
            }
        }
        if (!relaxed)return true;
    }
    for (int u = 1; u <= node_cnt; u++) {
        if (dist[u] == INF)continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] > dist[u] + w)
                return false;
        }
    }
    return true;
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
    bellman_ford(a, n);
    cout << (dist[b] == INF ? -1 : dist[b]);
}