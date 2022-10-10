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
int relax_cnt[N];
bool in_queue[N];

bool spfa(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = -INF;
        parent[i] = -1;
        relax_cnt[i] = 0;
        in_queue[i] = false;
    }
    queue<int> q;
    q.push(root);
    dist[root] = 0;
    parent[root] = -1;
    relax_cnt[root] = 1;
    in_queue[root] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        if (dist[u] == -INF) continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!in_queue[v]) {
                    if (++relax_cnt[v] == node_cnt)
                        return false;
                    q.push(v);
                    in_queue[v] = true;
                }
            }
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
    spfa(1, n);
    cout << (dist[n] == -INF ? -1 : dist[n]);
}