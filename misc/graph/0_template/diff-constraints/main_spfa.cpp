#include <iostream>
#include <algorithm>
#include <queue>

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
int relax_cnt[N];
bool in_queue[N];

bool bellman_ford(int root, int node_cnt) {
    // init
    queue<int> q;
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = -INF;
        in_queue[i] = false;
        relax_cnt[i] = 0;
    }
    dist[root] = 0;
    in_queue[root] = true;
    relax_cnt[root] = 1;
    q.push(root);
    //
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        if (dist[u] == -INF) continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
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