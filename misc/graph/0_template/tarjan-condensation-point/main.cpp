#include <iostream>
#include <algorithm>
#include <stack>

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
bool inStk[N];

void tarjan(int u) {
    stack<int> stk;
    dfn[u] = low[u] = ++num;
    inStk[u] = true;
    stk.push(u);
    for (int i = head[i]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (inStk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    // 当轮访问 回溯时，把
    if (low[u] == dfn[u]) {
        int v;
        cout << "强连通分量:";
        do {
            v = stk.top();
            stk.pop();
            inStk[v] = false;
            cout << v << " ";
        } while (v != u);
        cout << endl;
    }
}


int
main() {
}