#include <iostream>
#include <algorithm>

using namespace std;
#define N 10
#define M 100

struct edge {
    int to, w, next;
} edges[M];
int head[N], edge_cnt;
int n, m;

int dfn[N], low[N];
int num;

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++num;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to, weight = edges[i].w;
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {  // 判桥
                cout << u << "-" << v << endl;
            }
        }
        else {          // 遇到重复的
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int
main() {

}