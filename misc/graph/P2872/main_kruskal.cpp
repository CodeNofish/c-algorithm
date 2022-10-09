#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
#define N 1004
#define INF numeric_limits<double>::max()
#define M 1004

int n, m;

struct vertex {
    double x, y;

    [[nodiscard]] double dist_to(const vertex o) const {
        return sqrt((x - o.x) * (x - o.x) + (y - o.y) * (y - o.y));
    }
};

vertex vs[N];

struct edge {
    int from, to;
    double weight;

    bool operator<(const edge o) const {
        return weight < o.weight;
    }
};

edge es[M + N * N];

int pa[N], cc_num;

void init_uf() {
    for (int i = 1; i <= n; i++)
        pa[i] = i;
    cc_num = n;
}

int find(int x) {
    while (x != pa[x]) {
        pa[x] = pa[pa[x]];
        x = pa[x];
    }
    return x;
}

void merge(int x, int y) {
    if (find(x) != find(y)) {
        pa[find(x)] = find(y);
        cc_num--;
    }
}

bool connected(int x, int y) {
    return find(x) == find(y);
}

double kruskal(int edge_cnt) {
    double res = 0;
    sort(es, es + edge_cnt);
    init_uf();
    for (int i = 0; i < edge_cnt; i++) {
        int u = es[i].from, v = es[i].to;
        double w = es[i].weight;
        if (!connected(u, v)) {
            merge(u, v);
            res += w;
        }
    }
    return res;
}

int
main() {
    // 无向 最小生成树 prim
    int u, v;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> vs[i].x >> vs[i].y;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            es[cnt].from = i;
            es[cnt].to = j;
            es[cnt].weight = vs[i].dist_to(vs[j]);
            cnt++;
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        es[cnt].from = u;
        es[cnt].to = v;
        es[cnt].weight = 0;
        cnt++;
    }

    cout.precision(2);
    cout.flags(ios::fixed);
    cout.setf(ios::showpoint);
    cout << kruskal(cnt);
}