#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cfloat>

using namespace std;
#define INF DBL_MAX
#define N (1000+4)
#define M (N*N*4+4)

struct point {
    double x, y;

    double distTo(const struct point o) {
        return sqrt((x - o.x) * (x - o.x) + (y - o.y) * (y - o.y));
    }
};

point ps[N];

struct edge {
    int v, n;
    double w;
};
edge e[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, double w) {
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    head[u] = edge_cnt;
}

double dist[N];
int parent[N];
bool inU[N];

void dijkstra(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        dist[i] = INF;
        parent[i] = -1;
        inU[i] = false;
    }
    dist[root] = 0;
    parent[root] = -1;
    for (int k = 1; k <= node_cnt; k++) {
        // find min dist
        int u = -1;
        auto min = INF;
        for (int i = 1; i <= node_cnt; i++) {
            if (inU[i]) continue;
            if (min > dist[i]) {
                min = dist[i];
                u = i;
            }
        }
        if (u == -1) break;  // no more
        inU[u] = true;
        if (dist[u] == INF) continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v;
            double w = e[i].w;
            if (inU[v]) continue;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }
}


int
main() {
    double dr, rr;
    int n;
    int u, v;
    cin >> dr >> rr;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> ps[i].x >> ps[i].y;
    }
    cin >> u >> v;
    while (u != 0 && v != 0) {
        add_edge(u, v, ps[u].distTo(ps[v]) * rr);
        add_edge(v, u, ps[u].distTo(ps[v]) * rr);
        cin >> u >> v;
    }
    for (int i = n + 1; i <= n + 2; i++) {
        cin >> ps[i].x >> ps[i].y;
    }
    for (int i = 1; i <= n + 2; i++) {
        for (int j = 1; j <= n + 2; j++) {
            if (i == j) continue;
            add_edge(i, j, ps[i].distTo(ps[j]) * dr);
            add_edge(j, i, ps[i].distTo(ps[j]) * dr);
        }
    }

    dijkstra(n + 1, n + 2);
    cout.setf(ios::fixed);  // ????????????????????????
    cout.precision(4);
    cout << (dist[n] == INF ? -1 : dist[n + 2]);
}