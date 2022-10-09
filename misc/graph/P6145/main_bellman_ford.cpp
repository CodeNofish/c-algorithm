#include <iostream>
#include <algorithm>

using namespace std;
#define INF 0x7fffffff
#define N (100000+4)
#define M (N*2)

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

bool bellman_ford(int root, int node_cnt) {
    // init
    for (int i = 1; i <= node_cnt; i++)
        dist[i] = -INF;
    dist[root] = 0;
    // relax n-1 times
    for (int k = 0; k < node_cnt - 1; k++) {
        bool relaxed = false;
        for (int u = 1; u <= node_cnt; u++) {
            if (dist[u] == -INF)continue;
            for (int i = head[u]; i; i = e[i].n) {
                int v = e[i].v, w = e[i].w;
                if (dist[v] < dist[u] + w) {
                    dist[v] = dist[u] + w;
                    relaxed = true;
                }
            }
        }
        if (!relaxed) return true;
    }
    // test n
    for (int u = 1; u <= node_cnt; u++) {
        if (dist[u] == -INF)continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] < dist[u] + w) {
                return false;
            }
        }
    }
    return true;
}

// TLE
int
main() {
    int n, m, c, s;
    int a, b, x;
    // dist[b] - dist[a] >= x
    // ==> dist[b] >= dist[a] + x
    // ==> 更新条件 dist[b] < dist[a] + x[a,b] 判断最长路径
    cin >> n >> m >> c;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        add_edge(n + 1, i, s);
    }
    for (int i = 1; i <= c; i++) {
        cin >> a >> b >> x;
        add_edge(a, b, x);
    }
    bellman_ford(n + 1, n + 1);
    for (int i = 1; i <= n; i++)
        cout << dist[i] << '\n';
}