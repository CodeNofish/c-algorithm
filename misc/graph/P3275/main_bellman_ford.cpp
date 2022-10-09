#include <iostream>
#include <algorithm>

using namespace std;
#define INF 0x7fffffff
#define N (100000+4)
#define M (100000*2+N*4+4)

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
    int n, k;
    int mod, a, b;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> mod >> a >> b;
        switch (mod) {
            case 1:
                // a-b>=0  b-a<=0  update:b>a+0  <a,b,0>
                // a-b<=0  a<=b+0  update:a>b+0  <b,a,0>
                add_edge(a, b, 0);
                add_edge(b, a, 0);
                break;
            case 2:
                // a<b  a-b<=1  update:a>b+1  <b,a,1>
                add_edge(a, b, 1);
                break;
            case 3:
                // a>=b  b<=a  update:b>a+0  <a,b,0>
                add_edge(a, b, 0);
                break;
            case 4:
                // a>b  a-b>=1  update:b>a-1  <a,b,-1>
                add_edge(a, b, -1);
                break;
            case 5:
                // a<=b  update:a>b+0  <b,a,0>
                add_edge(b, a, 0);
                break;
            default:
                break;
        }
    }
    // dist[i] >= 1
    for (int i = 1; i <= n; i++)
        add_edge(n + 1, i, 1);
    //
//    for (int i = 1; i <= n; i++)
//        add_edge(n + 1, i, 0);
    if (bellman_ford(n + 1, n + 1)) {
        long long sum = 0;
//        for (int i = 1; i <= n; i++)
//            sum += dist[i];
//        cout << sum + n;
        for (int i = 1; i <= n; i++)
            cout << dist[i] << " ";
    }
    else {
        cout << "-1";
    }
}