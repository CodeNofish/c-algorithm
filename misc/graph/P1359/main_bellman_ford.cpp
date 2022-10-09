#include <iostream>
#include <algorithm>

using namespace std;

#define N 204
#define INF 0x7fffffff
int n, m;

struct edge {
    int from, to, w, next;
};
edge e[N * N];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    e[edge_cnt].from = u;
    e[edge_cnt].to = v;
    e[edge_cnt].w = w;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

int dist[N];    // min root->i path_len
int parent[N];

bool bellman_ford(int root) {
    // init dist
    for (int i = 1; i <= n; i++) {
        if (i == root) {
            dist[i] = 0;
            parent[i] = -1;
            continue;
        }
        dist[i] = INF;
        parent[i] = -1;
    }
    // relax n-1 times
    for (int i = 0; i < n - 1; i++) {
        bool relaxed = false;
        // emulate edges
        for (int j = 1; j <= edge_cnt; j++) {
            // dist[from] + form->to  better than dist[to]
            int u = e[j].from, v = e[j].to, w = e[j].w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                relaxed = true;
            }
        }
        if (!relaxed)
            return true;
    }
    // test n
    for (int j = 1; j <= edge_cnt; j++) {
        int u = e[j].from, v = e[j].to, w = e[j].w;
        if (dist[v] > dist[u] + w) {
            return false;
        }
    }
    return true;
}

int
main() {
    // bellman-ford  枚举边，松弛n-1次，若能继续松弛则有负环
    cin >> n;
    int val;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> val;
            // 有向图
            add_edge(i, j, val);
        }
    }
    bellman_ford(1);
    cout << dist[n];
}