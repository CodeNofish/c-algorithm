#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define N (100000+4)
#define M N<<1

struct edge {
    int u, v, w;

    bool operator<(const edge o) const {
        return w > o.w;
    }
};

edge e[M];

int pa[N], cc_cnt;

void init_uf(int n) {
    cc_cnt = n;
    for (int i = 1; i <= n; i++)
        pa[i] = i;
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
        pa[find(x)] = pa[find(y)];
        cc_cnt--;
    }
}

bool connected(int x, int y) {
    return find(x) == find(y);
}

int kruskal(int node_cnt, int edge_cnt, int k) {
    int res = 0;
    sort(e, e + edge_cnt);
    init_uf(node_cnt);
    for (int i = 0; i < edge_cnt; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (!connected(u, v)) {
            merge(u, v);
            res += w;
            if (node_cnt - cc_cnt == k)
                return res;
        }
    }
    return res;
}

int
main() {
    int n, m, k;
    int u, v, w;
    cin >> n >> m >> k;
    // k 条边的 最大生成树
    // prim 有初始点 不方便
    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    cout << kruskal(n, m, k);
}