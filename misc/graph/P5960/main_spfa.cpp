#include <iostream>
#include <algorithm>
#include <queue>

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
int relaxed_cnt[N];
bool in_queue[N];

bool spfa(int root, int node_cnt) {
    // init dist
    queue<int> q;
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
        in_queue[i] = false;
        relaxed_cnt[i] = 0;
    }
    dist[root] = 0;
    relaxed_cnt[root] = 1;
    q.push(root);
    in_queue[root] = true;
    // relax n-1 times
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].v, w = e[i].w;
            if (dist[u] == INF) continue;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!in_queue[v]) {
                    if (++relaxed_cnt[v] == node_cnt)
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
    int u, v, w;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        // u - v <= w[u,v]
//        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    // 超级源点
    for (int i = 1; i <= n; i++) {
        add_edge(n + 1, i, 0);
    }
    if (!spfa(n + 1, n + 1))
        cout << "NO";
    else {
        for (int i = 1; i <= n; i++)
            cout << dist[i] << ' ';
    }
}