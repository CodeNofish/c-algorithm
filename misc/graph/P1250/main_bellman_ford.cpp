#include <iostream>
#include <algorithm>

using namespace std;
#define INF 0x7fffffff
#define N (30000+4)
#define M (5000+N*3+4)

struct edge {
    int v, w, n;
};
edge edges[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    edges[edge_cnt].v = v;
    edges[edge_cnt].w = w;
    edges[edge_cnt].n = head[u];
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
            for (int i = head[u]; i; i = edges[i].n) {
                int v = edges[i].v, w = edges[i].w;
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
        for (int i = head[u]; i; i = edges[i].n) {
            int v = edges[i].v, w = edges[i].w;
            if (dist[v] < dist[u] + w)
                return false;
        }
    }
    return true;
}

// TLE
int
main() {
    int n, h;
    int b, e, t;
    cin >> n >> h;
    // 这时的dis[j]表示前j家种了多少颗树，ans=dis[n]
    // 每个部分为一个单位尺寸大小并最多可种一棵树。
    //
    // dist[e] - dist[b-1] >= t
    // => dist[e] >= t + dist[b-1]
    // update : dist[e] < dist[b-1] + t
    // => dist[e] < dist[b-1] + t[b-1,e]
    // => 最大路径 <b-1,e,t>
    for (int i = 1; i <= h; i++) {
        cin >> b >> e >> t;
        // add_edge(b - 1, e, t);
        add_edge(b, e + 1, t);
    }
    // 适配模板
    n = n + 1;

    // 已知 dist[n+1]=0 超级源点
    // dist[i] >= 0
    // => dist[i] - dist[n+1] >= 0
    for (int i = 1; i <= n; i++)
        add_edge(n + 1, i, 0);

    // dist[i+1] - dist[i] >= 0
    for (int i = 1; i <= n - 1; i++)
        add_edge(i, i + 1, 0);
    // dist[i+1] - dist[i] <= 1
    // dist[i] - dist[i+1] >= -1
    for (int i = 1; i <= n - 1; i++)
        add_edge(i + 1, i, -1);

    bellman_ford(n + 1, n + 1);
//    for (int i = 1; i <= n + 1; i++)
//        cout << dist[i] << " ";
    cout << dist[n];
}