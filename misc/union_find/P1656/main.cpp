#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <memory.h>
using namespace std;

#define N 150
#define M 5000
bool graph[N][N];

struct edge {
    int from;
    int to;
};
edge edges[M];

typedef void graph_vertex_visitor(int v);

// DFS遍历 图中某节点所在的联通分量
//
// seen[]   已经遍历过的点集
// n        遍历的起始点个数
// v        当前访问的点
void graph_vertex_dfs(bool seen[], int n, int v,
                      graph_vertex_visitor visit = nullptr) {
    if (seen[v]) return;
    seen[v] = true;
    if(visit) visit(v);   // do something
    for (int i = 0; i < n; ++i) {
        if (!seen[i] && graph[v][i])
            graph_vertex_dfs(seen, n, i, visit);
    }
}

// BFS遍历 图中某节点所在的联通分量
//
// seen[]   已经遍历过的点集
// n        遍历的起始点个数
// v        当前访问的点
void graph_vertex_bfs(bool seen[], int n, int v,
                      graph_vertex_visitor visit = nullptr) {
    if (seen[v]) return;
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if(visit) visit(v);   // do something
        seen[cur] = true;
        for (int next = 0; next < n; ++next) {
            if (!seen[next] && graph[cur][next])
                q.push(next);
        }
    }
}

// 计算联通分量个数 (还可以用并查集计算)
int graph_connected_component(bool seen[], int n) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (!seen[i]) {
            cnt++;
            graph_vertex_bfs(seen, n, i);
        }
    }
    return cnt;
}

//
int graph_cut_points(int n, int res[]) {
    int find = 0;
    bool seen[n];
    memset(seen, 0, n);

    // 原来的联通分量
    int raw_cc = graph_connected_component(seen, n);
    int modified_cc = raw_cc;

    for (int i = 0; i < n; ++i) {
        memset(seen, 0, n);
        seen[i] = true;     // 不遍历当前点
        modified_cc = graph_connected_component(seen, n);
        if (modified_cc > raw_cc)
            res[find++] = i;
    }
    return find;
}

int graph_cut_edges(int n) {
    int find = 0;
    bool seen[n];
    memset(seen, 0, n);
    // 原来的联通分量
    int raw_cc = graph_connected_component(seen, n);
    int modified_cc;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (graph[i][j]) {
                memset(seen, 0, n);
                graph[i][j] = false;    // 不遍历当前边
                graph[j][i] = false;
                modified_cc = graph_connected_component(seen, n);
                graph[i][j] = true;
                graph[j][i] = true;
                if (modified_cc > raw_cc) {
                    edges[find].from = j;
                    edges[find].to = i;
                    find++;
                }
            }
        }
    }
    return find;
}

// 打印图 按连通分量换行
void print_graph(int n) {
    bool seen[n];
    memset(seen, 0, n);
    for (int i = 0; i < n; ++i) {
        if (!seen[i]) {
            graph_vertex_dfs(seen, n, i, [](int v){
                cout << v << " ";
            });
            cout << "\n";
        }
    }
}

// Tarjan 求解无向图的所有割边(桥)
int
main()
{
    int n,m;
    int a,b;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        memset(graph[i], 0, n);
    }
    for(int i = 0; i < m; ++i) {
        cin >> a >> b;
        graph[a-1][b-1] = true;
        graph[b-1][a-1] = true;
    }

    int find = graph_cut_edges(n);
    sort(edges, edges + find, [](edge a, edge b){
        if (a.from == b.from)   return a.to < b.to;
        return a.from < b.from;
    });
    for (int i = 0; i < find; ++i) {
        cout << edges[i].from + 1 << " " << edges[i].to + 1 << endl;
    }

}