#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define N (1000000+4)
#define M (2000000+4)
#define MOD 100003
int n,m;
struct edge {
    int to,w,nex;
};
edge e[M];
int head[N], cnt, edge_size;
void add_edge(int u, int v, int w) {
    // 去重边 自环
//    if (u == v) return;
//    for (int i = head[u]; i != 0; i = e[i].nex) {
//        if (e[i].to == v) {
//            e[i].w = min(e[i].w, w);
//        }
//    }
//    edge_size++;
    // normal
    cnt++;
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].nex = head[u];
    head[u] = cnt;
}

struct pq_node{
    int dis,pos;
    bool operator <(const pq_node &x) const {
        return dis > x.dis;
    }
};

bool seen[N];
int dis[N];
int path_cnt[N];
void dijkstra(int root) {
    priority_queue<pq_node> pq;
    for (int i = 1; i <= n; ++i) {
        seen[i] = false;
        path_cnt[i] = 0;
        dis[i] = 0x7fffffff;
    }
    dis[root] = 0;
    path_cnt[root] = 1;
    pq.push(pq_node{path_cnt[root], root});
    while (!pq.empty()) {
        pq_node tmp = pq.top();pq.pop();
        int u = tmp.pos, d = tmp.dis;
        if (seen[u]) continue;
        seen[u] = true;
        for (int i = head[u]; i != 0; i = e[i].nex) {
            int v = e[i].to;
            if (seen[v]) continue;
            if (dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                path_cnt[v] = path_cnt[u];
                pq.push(pq_node{dis[v],v});
            } else if (dis[v] == dis[u] + e[i].w) {
                path_cnt[v] += path_cnt[u];
                path_cnt[v] %= MOD;
            }
        }
    }
}

// 无向无权图
int
main()
{
    int x,y;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y;
        add_edge(x, y, 1);
        add_edge(y, x, 1);  // 走过的边数 作为权
    }
    dijkstra(1);
    for (int i = 1; i <= n; ++i) {
        cout << path_cnt[i] << "\n";
    }
}