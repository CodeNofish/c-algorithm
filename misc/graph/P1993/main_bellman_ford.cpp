#include <iostream>
#include <algorithm>

using namespace std;
#define INF 0x7fffffff
#define N (5000+4)
#define M (5000+4+N*4)

struct edge {
    int v, w, n;
};
edge e[M];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    e[edge_cnt].v = v;
    e[edge_cnt].w = w;
    e[edge_cnt].n = head[u];
    head[u] = edge_cnt;
}

int dist[N];

bool bellman_ford(int root, int node_cnt) {
    for (int i = 1; i <= node_cnt; i++)
        dist[i] = INF;
    dist[root] = 0;
    // relax n-1 times
    for (int k = 0; k < node_cnt - 1; k++) {
        bool relaxed = false;
        for (int u = 1; u <= node_cnt; u++) {
            if (dist[u] == INF)continue;
            for (int i = head[u]; i; i = e[i].n) {
                int v = e[i].v, w = e[i].w;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    relaxed = true;
                }
            }
        }
        if (!relaxed)return true;
    }
    for (int u = 1; u <= node_cnt; u++) {
        if (dist[u] == INF)continue;
        for (int i = head[u]; i; i = e[i].n) {
            int v = e[i].v, w = e[i].w;
            if (dist[v] > dist[u] + w)
                return false;
        }
    }
    return true;
}

int
main() {
    int n, m, mod;
    int a, b, c;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> mod;
        cin >> a >> b;
        switch (mod) {
            case 1:
                // a-b>=c
                // => b-a<=-c
                // update: b>a+(-c)[a,b]
                cin >> c;
                add_edge(a, b, -c);
                break;
            case 2:
                // a-b<=c
                // update: a>b+c[b,a]
                cin >> c;
                add_edge(b, a, c);
                break;
            case 3:
                // a-b<=0 <b,a,0>
                // a-b>=0 <a,b,0>
                add_edge(b, a, 0);
                add_edge(a, b, 0);
                break;
            default:
                break;
        }
    }
    // add super node
    for (int i = 1; i <= n; i++) {
        add_edge(n + 1, i, 0);
    }
    bool f = bellman_ford(n + 1, n + 1);
    if (!f)
        cout << "No";
    else
        cout << "Yes";
}