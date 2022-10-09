#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define N (10000+4)
int n;

vector<int> G[N];
int in_degree[N], out_degree[N];

void add_edge(int u, int v, int w) {
    G[u].push_back(v);
    in_degree[v]++;
    out_degree[u]++;
}

int topo[N];
bool seen[N];

// dp_i = max{pre_i} + a_i
int dp[N];
int vertex_val[N];

void topo_sort() {
    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        seen[i] = false;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
            // dp init
            dp[i] = vertex_val[i];
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo[++cnt] = u;
        for (int v: G[u]) {
            // u->v
            dp[v] = max(dp[v], dp[u] + vertex_val[v]);

            if (!seen[v] && --in_degree[v] == 0) {
                seen[v] = true;
                q.push(v);
            }
        }
    }
}


int
main() {
    int to, from;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> to >> vertex_val[i];
        cin >> from;
        while (from != 0) {
            add_edge(from, to, 1);
            cin >> from;
        }
    }
    topo_sort();
    int res = 0;
    for (int i = 1; i <= n; i++)
        res = max(res, dp[i]);
    cout << res;
}