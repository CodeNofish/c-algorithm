#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define N 10
#define M 100

struct edge {
    int to, w, next;
} edges[M];
int head[N], edge_cnt;

int in_degree[N];
int n, m;

int topo[N];
bool seen[N];

void topo_sort() {
    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0)
            q.push(i);
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        topo[++cnt] = cur;
        seen[cur] = true;
        for (int i = head[cur]; i != 0; i = edges[i].next) {
            int to = edges[i].to, weight = edges[i].w;
            if (!seen[to] && --in_degree[cur] == 0)
                q.push(to);
        }
    }
}

int ve[N], vl[N];   // 点 最早 最迟
int ee[M], el[M];     // 边 最早 最迟

queue<int> critical_path() {
    topo_sort();
    // 顺拓扑 求ve  ve[v] = max(ve[u] + edge_uv.w)
    for (int i = 1; i <= n; i++)
        ve[i] = 0;
    for (int j = 1; j <= n; j++) {
        int u = topo[j];
        for (int i = head[u]; i; i = edges[i].next) {
            int v = edges[i].to, weight = edges[i].w;
            if (ve[v] < ve[u] + weight)
                ve[v] = ve[u] + weight;
        }
    }
    // 逆拓扑 求vl  vl[u] = min(vl[v] - edge_uv.w)
    for (int i = 1; i <= n; i++)
        vl[i] = ve[n];
    for (int j = n; j >= 0; j--) {
        int u = topo[j];
        for (int i = head[u]; i; i = edges[i].next) {
            int v = edges[i].to, weight = edges[i].w;
            if (vl[u] > vl[v] - weight)
                vl[u] = vl[v] - weight;
        }
    }
    // a=from-to    e[from]=ve[from]    l[from]=le[from]-a.w
    queue<int> key_path;
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = edges[i].next) {
            int v = edges[i].to, weight = edges[i].w;
            ee[i] = ve[u];
            el[i] = vl[v] - weight;
            // ee[i] == el[i]
            // key path
            if (ee[i] == el[i]) {
                key_path.push(i);
            }
        }
    }
    return key_path;
}


int
main() {
    cin >> n >> m;
}