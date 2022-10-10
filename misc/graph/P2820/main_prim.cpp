#include <iostream>
#include <algorithm>

using namespace std;
#define INF 0x7fffffff
#define N (100+4)
#define M N*N

int G[N][N];

int total_min = 0;    // 最小生成树的长度

int lowcost[N];
int closest[N];
bool inU[N];

void prim(int root, int node_cnt, int edge_cnt) {
    for (int i = 1; i <= node_cnt; i++) {
        lowcost[i] = G[root][i] == 0 ? INF : G[root][i];
        closest[i] = G[root][i] == 0 ? -1 : root;
        inU[i] = false;
    }
    lowcost[root] = 0;
    closest[root] = -1;
    inU[root] = true;
    for (int k = 1; k <= node_cnt; k++) {
        // find lowcost edge
        int min = INF, u = -1;
        for (int i = 1; i <= node_cnt; i++) {
            if (inU[i]) continue;
            if (min > lowcost[i]) {
                min = lowcost[i];
                u = i;
            }
        }
        if (u == -1) break;
        inU[u] = true;
        for (int v = 1; v <= node_cnt; v++) {
            if (inU[v]) continue;
            if (G[u][v] == 0) continue;
            // use u->v update lowcost[]
            if (lowcost[v] > G[u][v]) {
                lowcost[v] = G[u][v];
                closest[v] = u;
            }
        }
    }
    for (int i = 1; i <= node_cnt; i++)
        total_min += lowcost[i];    // choose cur edge
}

int
main() {
    // 最小生成树
    int n, m;
    int u, v, w;
    cin >> n >> m;
    int total_w = 0;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        G[u][v] = w;
        G[v][u] = w;
        total_w += w;
    }
    prim(1, n, m);
    cout << (total_w - total_min);
}