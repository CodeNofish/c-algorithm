#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define INF 0x7fffffff
#define N (1000+4)
#define M (5000+N+4)

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

bool spfa(int root, int node_cnt) {
    queue<int> q;
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
        relax_cnt[i] = 0;
        in_queue[i] = false;
    }
    q.push(root);
    dist[root] = 0;
    relax_cnt[root] = true;
    in_queue[root] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        if (dist[u] == INF)continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] > dist[u] + w) {
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
    int n, m;
    int ti, tj, b;
    cin >> n >> m;
    // i - j <= b
    // => dist[i] <= dist[j] + b
    // update: dist[i] > dist[j] + b[j,i]
    for (int i = 0; i < m; i++) {
        cin >> ti >> tj >> b;
        add_edge(tj, ti, b);
    }
    // 为什么不直接使用 dist[i] <= 0 ?
    // 使用<i,n+1,0> 会导致 图无法连通,SPFA跑出来INF就不行了
    //
    // dist[i] <= 0
    // => dist[i] - dist[n+1] <= 0
    // => <n+1, i, 0>
    for (int i = 1; i <= n; i++)
        add_edge(n + 1, i, 0);

    if (spfa(n + 1, n + 1)) {
        int min = INF;
        for (int i = 1; i <= n; i++)
            min = min < dist[i] ? min : dist[i];
        for (int i = 1; i <= n; i++)
            cout << dist[i] - min << '\n';
    }
    else {
        cout << "NO SOLUTION";
    }
}