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

double dist[N][N];
int parent[N][N];

bool floyd(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        for (int j = 1; j <= node_cnt; j++) {
            dist[i][j] = INF;
            parent[i][j] = -1;
        }
        dist[i][i] = 0;
    }
    for (int u = 1; u <= node_cnt; u++) {
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v;
            double w = e[i].w;
            dist[u][v] = w;
            parent[u][v] = u;
        }
    }
    for (int k = 1; k <= node_cnt; k++) {
        for (int i = 1; i <= node_cnt; i++) {
            for (int j = 1; j <= node_cnt; j++) {
                if (dist[i][k] == INF || dist[k][j] == INF) continue;
                // use k to relax
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[i][k];
                }
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

    floyd(n + 1, n + 2);
    cout.setf(ios::fixed);  // 一起使用固定长度
    cout.precision(4);
    cout << dist[n + 1][n + 2];
}