#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define N 1004
#define INF numeric_limits<double>::max()

int n, m;

struct vertex {
    double x, y;

    [[nodiscard]] double dist_to(const vertex o) const {
        return sqrt((x - o.x) * (x - o.x) + (y - o.y) * (y - o.y));
    }
};

vertex vs[N];

double G[N][N];

double lowcost[N];
int parent[N];
bool inU[N];

void prim(int root) {
    // init
    for (int i = 1; i <= n; i++) {
        if (i == root) {
            lowcost[i] = 0;
            parent[i] = -1;
            inU[i] = true;
            continue;
        }
        lowcost[i] = G[root][i];
        parent[i] = root;
        inU[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        // find min lowcost in U-V
        double min = INF;
        int next = -1;
        for (int j = 1; j <= n; j++) {
            if (!inU[j] && min > lowcost[j]) {
                min = lowcost[j];
                next = j;
            }
        }
        // can't find more
        if (next == -1)break;
        // add next to U
        inU[next] = true;
        // update lowcost&parent by next
        for (int j = 1; j <= n; j++) {
            if (!inU[j] && lowcost[j] > G[next][j]) {
                lowcost[j] = G[next][j];
                parent[j] = next;
            }
        }
    }
}

double path_sum() {
    double res = 0;
    for (int i = 1; i <= n; i++)
        res += lowcost[i];
    return res;
}

int
main() {
    // 无向 最小生成树 prim
    int u, v;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> vs[i].x >> vs[i].y;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) G[i][j] = 0;
            G[i][j] = vs[i].dist_to(vs[j]);
        }
    }
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        G[u][v] = 0;
        G[v][u] = 0;
    }
    prim(1);
    cout.precision(2);
    cout.flags(ios::fixed);
    cout.setf(ios::showpoint);
    cout << path_sum();
}