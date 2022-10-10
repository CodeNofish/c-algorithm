#include <iostream>
#include <algorithm>

using namespace std;
#define N (100+4)
#define M N*N

struct edge {
    int u, v, w;

    bool operator<(const edge o) const {
        return w < o.w;
    }
};

edge e[M];

int pa[N], cc_cnt;

void init_uf(int n) {
    for (int i = 1; i <= n; i++)
        pa[i] = i;
    cc_cnt = n;
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
        cc_cnt--;
    }
}

bool connected(int x, int y) {
    return find(x) == find(y);
}

int total_min = 0;    // 最小生成树的长度

void kruskal(int node_cnt, int edge_cnt) {
    sort(e + 1, e + 1 + edge_cnt);
    init_uf(node_cnt);
    for (int i = 1; i <= edge_cnt; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (!connected(u, v)) {
            merge(u, v);
            total_min += w;
            if (cc_cnt == 1)
                return;
        }
    }
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
        e[i].u = u;
        e[i].v = v;
        e[i].w = w;
        total_w += w;
    }
    kruskal(n, m);
    cout << (total_w - total_min);
}