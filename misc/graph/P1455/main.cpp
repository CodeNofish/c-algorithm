#include <iostream>
#include <algorithm>

using namespace std;
#define N (10000+4)
#define M (5000*2+N)
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

// 价钱 价值
int c[N], d[N];

// =====
int dfn[N], low[N], id;
int stack[N], top = 0;
bool in_stk[N];

int belong[N];              // 属于哪个强连通分量
int scc_id = 0;             // 强连通分量 Strongly connected component
int scc_c[N];               // 强连通分量的统计值
int scc_d[N];

void tarjan(int root, int parent) {
    dfn[root] = low[root] = ++id;
    stack[++top] = root;
    in_stk[root] = true;
    for (int i = head[root]; i; i = e[i].n) {
        int v = e[i].v;
        if (!dfn[v]) {
            tarjan(v, parent);
            low[root] = min(low[root], dfn[v]);
        }
        if (in_stk[v]) {     // 在当前环内
            low[root] = min(low[root], low[v]);
        }
    }
    // 回溯当前环
    if (dfn[root] == low[root]) {   // 当前为非环节点
        int v;
        scc_id++;
        do {
            v = stack[top--];
            in_stk[v] = false;
            // 强连通分量
            belong[v] = scc_id;
            scc_c[scc_id] += c[v];
            scc_d[scc_id] += d[v];
        } while (v != root);
    }
}

//int dp[]
int
main() {
    int n, m, w;
    int ui, vi;
    cin >> n >> m >> w;
    for (int i = 1; i <= n; i++)
        cin >> c[i] >> d[i];
    for (int i = 1; i <= m; i++) {
        cin >> ui >> vi;
        add_edge(ui, vi, 1);
        add_edge(vi, ui, 1);
    }
    for (int u = 1; u <= n; u++) {
        if (!dfn[u])
            tarjan(u, u);
    }
    for (int i = 1; i <= scc_id; i++) {

    }
}