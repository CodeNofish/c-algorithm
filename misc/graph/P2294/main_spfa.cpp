#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define INF 0x7fffffff
#define N (100+4)
#define M (1000*2+N*4+4)
struct edge {
    int v, w, n;
};
edge e[M];
int head[N], edge_cnt = 0;

void init_edge(int n) {
    n = min(N, n);
    edge_cnt = 0;
    for (int i = 0; i < n; i++)
        head[i] = 0;
}

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
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
        relax_cnt[i] = 0;
        in_queue[i] = false;
    }
    queue<int> q;
    q.push(root);
    in_queue[root] = true;
    dist[root] = 0;
    relax_cnt[root] = 1;
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
    int w, n, m;
    int s, t, v;
    cin >> w;
    while (w--) {
        cin >> n >> m;
        init_edge(n + 4);
        for (int i = 0; i < m; i++) {
            cin >> s >> t >> v;
            // dist[t] - dist[s-1] == v
            // dist[t] - dist[s-1] >= v  =>  dist[s-1] <= dist[t] + (-v)[t,s-1]
            // dist[t] - dist[s-1] <= v  =>  dist[t] <= dist[s-1] + v[s-1,t]
            add_edge(t + 1, s, -v);
            add_edge(s, t + 1, v);
        }
        n = n + 1;  // fix
        for (int i = 1; i <= n; i++)
            add_edge(n + 1, i, 0);
        if (spfa(n + 1, n + 1))
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
}