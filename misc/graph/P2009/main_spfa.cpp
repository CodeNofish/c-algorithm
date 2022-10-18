#include <iostream>
#include <algorithm>
#include <queue>
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
int relax_cnt[N];
bool in_que[N];

bool spfa(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
        parent[i] = -1;
        relax_cnt[i] = 0;
        in_que[i] = false;
    }
    queue<int> q;
    q.push(root);
    dist[root] = 0;
    parent[root] = -1;
    relax_cnt[root] = 1;
    in_que[root] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_que[u] = false;
        if (dist[u] == INF) continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!in_que[v]) {
                    if (++relax_cnt[v] == node_cnt)
                        return false;
                    q.push(v);
                    in_que[v] = true;
                }
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
    spfa(x - 'A' + 1, n);
    cout << dist[y - 'A' + 1];
}