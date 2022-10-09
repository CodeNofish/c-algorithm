#include <iostream>
#include <algorithm>

using namespace std;
#define N (100+4)
#define INF 0x7fffffff
#define M N*N
int n;

struct edge {
    int u, v, w;

    bool operator<(const edge o) const {
        return w < o.w;
    }
};

edge e[M];

int pa[N];
int cc_num;

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

int kruskal(int edge_num) {
    int res = 0;
    sort(e, e + edge_num);
    init_uf();
    for (int i = 0; i < edge_num; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (!connected(u, v)) {
            merge(u, v);
            res += w;
        }
    }
    return res;
}

int
main() {
    cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            e[cnt].u = i;
            e[cnt].v = j;
            cin >> e[cnt].w;
            cnt++;
        }
    }
    cout << kruskal(cnt);
}