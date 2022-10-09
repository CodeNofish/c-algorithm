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

void tarjan(int u, int fa, int root) {
    dfn[u] = low[u] = ++num;
    int child_cnt = 0;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, u, root);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {     // 割点
                if (u != root || ++child_cnt > 1)
                    cout << u << endl;
            }
        }
        else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int
main() {

}