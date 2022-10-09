#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define N 2504
#define M 6204
#define INF 0x7fffffff

// 根据入点访问，都可以用向前星
struct edge {
    int v, w, n;
};
edge e[M * 2];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    head[u] = edge_cnt;
}

int n, m, s, t;

int dist[N];
int parent[N];
bool inU[N];

void dijkstra(int root) {
    // init dist
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        inU[i] = false;
    }
    priority_queue<pair<int, int>> heap;     // 想要小顶 输入取反
    dist[root] = 0;
    heap.push(make_pair(0, root));
    // add close vertex to U and update dist
    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (inU[u]) continue;
        inU[u] = true;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (!inU[v] && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                heap.push(make_pair(-dist[v], v));
            }
        }
    }
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
    dijkstra(s);
    cout << dist[t];
}