#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define N 2504
#define M 6204
#define INF 0x7fffffff

struct edge {
    int v, w, n;
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
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    head[u] = edge_cnt;
}

int n, m, s, t;

int dist[N];
int parent[N];
int relax_cnt[N];       // 松弛次数
bool in_queue[N];       // 是否在队列
bool spfa(int root) {
    // init
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        relax_cnt[i] = 0;
        in_queue[root] = false;
    }
    dist[root] = 0;
    relax_cnt[root] = 1;
    in_queue[root] = true;
    q.push(root);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[u] == INF) continue;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!in_queue[v]) {
                    if (++relax_cnt[v] == n)
                        return false;
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return true;
}

// 队列优化 bellman-ford
int
main() {
    int u, v, w;
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    spfa(s);
    cout << dist[t];
}