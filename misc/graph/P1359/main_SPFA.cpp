#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define N 204
#define INF 0x7fffffff
int n, m;

struct edge {
    int from, to, w, next;
};
edge e[N * N];
int head[N], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    edge_cnt++;
    e[edge_cnt].from = u;
    e[edge_cnt].to = v;
    e[edge_cnt].w = w;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

int dist[N];            // min root->i path_len
int parent[N];
bool in_queue[N];       // has added to queue
int relax_cnt[N];       // relax time

bool SPFA(int root) {
    // init dist
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (i == root) {
            q.push(i);
            dist[i] = 0;
            parent[i] = -1;
            in_queue[i] = true;
            relax_cnt[i] = 1;
            continue;
        }
        dist[i] = INF;
        parent[i] = -1;
        in_queue[i] = false;
        relax_cnt[i] = 0;
    }
    //
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        in_queue[cur] = false;
        //
        for (int i = head[cur]; i != 0; i = e[i].next) {
            int next = e[i].to, w = e[i].w;
            if (dist[next] > dist[cur] + w) {
                dist[next] = dist[cur] + w;
                parent[next] = cur;
                if (!in_queue[next]) {
                    if (++relax_cnt[next] >= n)
                        return false;
                    q.push(next);
                    in_queue[next] = true;
                }
            }
        }
    }
    return true;
}

int
main() {
    // SPFA 队列优化bellman-ford
    // 只在松弛过的点上继续松弛
    cin >> n;
    int val;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> val;
            // 有向图
            add_edge(i, j, val);
        }
    }
    SPFA(1);
    cout << dist[n];
}