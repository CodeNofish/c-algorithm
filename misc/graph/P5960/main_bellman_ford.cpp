#include <iostream>
#include <algorithm>

using namespace std;
#define INF 0x7fffffff
#define N (5000+4)
#define M (N*2)

int n, m;
struct edge {
    int v, w, next;
};
edge e[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

int dist[N];

bool bellman_ford(int root, int node_cnt) {
    // init dist
    for (int i = 1; i <= node_cnt; i++)
        dist[i] = INF;
    dist[root] = 0;
    // relax n-1 times
    for (int k = 0; k < node_cnt - 1; k++) {
        bool relaxed = false;
        for (int u = 1; u <= node_cnt; u++) {
            if (dist[u] == INF) continue;
            for (int j = head[u]; j; j = e[j].next) {
                int v = e[j].v, w = e[j].w;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    relaxed = true;
                }
            }
        }
        if (!relaxed)return true;
    }
    // test n
    for (int u = 1; u <= node_cnt; u++) {
        if (dist[u] == INF) continue;
        for (int j = head[u]; j; j = e[j].next) {
            int v = e[j].v, w = e[j].w;
            if (dist[v] > dist[u] + w) {
                return false;
            }
        }
    }
    return true;
}

int
main() {
    int u, v, w;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        // v - u <= w[u,v]
        // v <= w[u,v] + u
//        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    // 超级源点 (注意: 使用了额外的边空间)
    for (int i = 1; i <= n; i++) {
        add_edge(n + 1, i, 0);
    }
    if (!bellman_ford(n + 1, n + 1))
        cout << "NO";
    else {
        for (int i = 1; i <= n; i++)
            cout << dist[i] << ' ';
    }
}