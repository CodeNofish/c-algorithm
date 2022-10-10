#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define N (100+4)
#define M N*N
#define INF 0x7fffffff
struct edge {
    int v, w, n;
    bool broken;
};
edge e[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    e[edge_cnt].broken = false;
    head[u] = edge_cnt;
}

void add_broken(int u, int v) {
    for (int i = head[u]; i; i = e[i].n)
        if (v == e[i].v)
            e[i].broken = true;
}

int get_weight(int idx) {
    if (e[idx].broken)
        return e[idx].w;
    return 0;
}

int dist[N];
int parent[N];
int relax_cnt[N];
bool in_queue[N];

bool spfa(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
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
        if (dist[u] == INF)continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = get_weight(i);
            if (dist[v] > dist[u] + w) {
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
    int n, m, d;
    int u, v, w;
    // 把好的路 视作边权为0的 求最短路径
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    cin >> d;
    for (int i = 0; i < d; i++) {
        cin >> u >> v;
        add_broken(u, v);
        add_broken(v, u);
    }
    cin >> u >> v;
    spfa(u, n);
    cout << dist[v];
}