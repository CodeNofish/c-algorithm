#include <iostream>
#include <algorithm>

using namespace std;

#define N 204
#define INF 0x7fffffff
int n, m;

int G[N][N];

int dist[N];    // min root->i path_len
int parent[N];
bool inU[N];    // have used to update dist
void dijkstra(int root) {
    for (int i = 1; i <= n; i++) {
        if (i == root) {
            inU[i] = true;
            dist[i] = 0;
            parent[i] = -1;
            continue;
        }
        parent[i] = G[root][i] == INF ? -1 : root;
        dist[i] = G[root][i];
        inU[i] = false;
    }
    for (int i = 1; i <= n; i++) {
        // find min dist
        int min = INF, t = -1;
        for (int j = 1; j <= n; j++) {
            if (!inU[j] && min > dist[j]) {
                min = dist[j];
                t = j;
            }
        }
        if (t == -1) break;
        inU[t] = true;
        // update dist by t
        for (int j = 1; j <= n; j++) {
            if (!inU[j] && G[t][j] < INF && dist[j] > dist[t] + G[t][j]) {
                dist[j] = dist[t] + G[t][j];
                parent[j] = t;
            }
        }
    }
}

int
main() {
    // dijkstra 贪心选取新节点 用新节点更新最短路径
    cin >> n;
    int val;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G[i][j] = INF;
    for (int i = 1; i <= n; i++) {
        G[i][i] = 0;
        for (int j = i + 1; j <= n; j++) {
            cin >> val;
            // 有向图
            G[i][j] = val;
        }
    }
    dijkstra(1);
    cout << dist[n];
}