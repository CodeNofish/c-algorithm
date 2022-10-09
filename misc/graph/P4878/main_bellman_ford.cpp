#include <iostream>
#include <algorithm>

using namespace std;
#define INF 0x7fffffff
#define N (1000+4)
#define M (10000*2+N*4+4)

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
    for (int i = 1; i <= node_cnt; i++)
        dist[i] = INF;
    dist[root] = 0;
    for (int k = 0; k < node_cnt - 1; k++) {
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
    int n, ml, md;
    int a, b, d;
    cin >> n >> ml >> md;
    // dist[b] - dist[a] <= d
    // => dist[b] <= dist[a] + d;
    // update condition: dist[b] > dist[a] + d[a,b];
    // min path <a,b,d>
    for (int i = 0; i < ml; i++) {
        cin >> a >> b >> d;
        add_edge(a, b, d);
    }
    // dist[b] - dist[a] >= d
    // => dist[a] - dist[b] <= -d
    // => dist[a] <= dist[b] + (-d)
    // update condition: dist[a] > dist[b] + (-d)[b,a]
    // min path <b,a,-d>
    for (int i = 0; i < md; i++) {
        cin >> a >> b >> d;
        add_edge(b, a, -d);
    }

    // dist[i] <= 0 && dist[n+1] == 0
    // => dist[i] - dist[n+1] <= 0
    // min path <n+1,i,0>
    for (int i = 1; i <= n; i++) {
        // 只有从特殊点访问才能用上,用上时保证全部可达;spfa(n+1)可以判断是否存在负环
        add_edge(n + 1, i, 0);
    }

    // dist[i+1] >= dist[i] 顺序排队
    // => dest[i+1] - dist[i] >= 0
    // min path <i+1,i,0>
    for (int i = 1; i <= n - 1; i++) {
        add_edge(i + 1, i, 0);
    }

    bool f1 = bellman_ford(n + 1, n + 1);     // 判断有无负环
    // 求解,
    // 通过dist[i+1] >= dist[i], 保证答案递增, bellman_ford[0] 保证dist[0]=0 找该条件下的一组解
    bool f2 = bellman_ford(1, n + 1);

    if (!f1)
        cout << "-1";
    else if (dist[n] == INF)
        cout << "-2";
    else
        cout << dist[n];
}