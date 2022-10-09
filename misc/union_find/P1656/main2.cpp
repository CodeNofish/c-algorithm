#include <iostream>
#include <vector>
using namespace std;

#define N 150
#define M 5000

vector<int> G[N];
bool seen[N];
int cnt = 0;
int dfn[N], low[N], parent[N];
bool cut_point[N];

int cut_edge_cnt = 0;
int cut_edges[N<<1];

void tarjan(int cur, int root) {
    // consider root
    int children_tree = 0;
    seen[cur] = true;
    dfn[cur] = low[cur] = ++cnt;
    for (auto next : G[cur]) {
        // 树边
        if (!seen[next]) {
            if (root == cur)    children_tree++;
            parent[next] = cur;
            tarjan(next, root);
            low[cur] = min(low[cur], low[next]);

            if (low[next] > dfn[cur]) {    // 它必须 经过我 才能访问到之前的
                cut_point[cur] = true;
                cut_edges[cut_edge_cnt*2] = cur;
                cut_edges[cut_edge_cnt*2+1] = next;
                cut_edge_cnt++;
            }
        }
        // 回边
        else if (next != parent[cur]) {
            low[cur] = min(low[cur], dfn[next]);
        }
    }
    if (cur == root && children_tree >= 2) {
        cut_point[cur] = true;
    }
}

struct Edge {
    int from, to;
};
bool operator <(Edge a, Edge b) {
    if (a.from==b.from) return a.to < b.to;
    return a.from<b.from;
}

int
main()
{
    int n,m;
    int a,b;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        G[a-1].push_back(b-1);
        G[b-1].push_back(a-1);
    }
    for (int i = 0; i < n; ++i) {
        if (!seen[i])
            tarjan(i, i);
    }
    Edge* e = (Edge*)cut_edges;
    sort(e, e+cut_edge_cnt);

    for (int i = 0; i < cut_edge_cnt; ++i) {
        cout << cut_edges[i*2]+1 << " " << cut_edges[i*2+1]+1 << endl;
    }
}