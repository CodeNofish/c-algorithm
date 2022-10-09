#include <iostream>
#include <algorithm>

using namespace std;

#define N 10

struct Edge {
    int u, v, w;
} e[N * N];
int m;      // 边数目

int fa[N];
int c_cnt;

bool cmp(Edge x, Edge y) {
    return x.w < y.w;
}

void uf_init(int n) {
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    c_cnt = n;
}

int find(int x) {
    while (x != fa[x]) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

void merge(int x, int y) {
    int px = find(x), py = find(y);
    if (px != py) {
        fa[px] = py;
        c_cnt--;
    }
}

int kruskal(int n) {
    int ans = 0;    // 最小生成树值
    sort(e, e + m, cmp);
    uf_init(n);
    for (int i = 0; i < m; i++) {
        int from = e[i].u, to = e[i].v, weight;
        // chose cur edge
        if (find(from) == find(to)) {
            merge(from, to);
            ans += weight;
            if (c_cnt == 1)
                return ans;
        }
    }
    return 0;
}

int
main() {

}