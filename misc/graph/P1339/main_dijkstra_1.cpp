#include <iostream>
#include <algorithm>

using namespace std;
#define N 2504
#define M 6204
#define INF 0x7fffffff

int G[N][N];

int n, m, s, t;

int dist[N];
int parent[N];
bool inU[N];

void dijkstra(int root) {
    // init dist
    for (int i = 1; i <= n; i++) {
        if (root == i) {
            dist[i] = 0;
            inU[i] = true;
            parent[i] = -1;
            continue;
        }
        dist[i] = G[root][i];
        inU[i] = false;
        parent[i] = G[root][i] == INF ? -1 : root;
    }
    // add close vertex to U and update dist
    for (int i = 1; i <= n; i++) {
        int min = INF, u = -1;
        for (int j = 1; j <= n; j++) {
            if (!inU[j] && min > dist[j]) {
                min = dist[j];
                u = j;
            }
        }
        //
        if (u == -1)break;
        // add to U
        inU[u] = true;
        // update dist
        for (int v = 1; v <= n; v++) {
            int w = G[u][v];
            if (inU[v] || w == INF) continue;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }
}

int
main() {
    int u, v, w;
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G[i][j] = INF;
        }
    }
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        G[u][v] = w;
        G[v][u] = w;
    }
    dijkstra(s);
    cout << dist[t];
}