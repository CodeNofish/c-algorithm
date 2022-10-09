#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define N (1000+4)
#define M (100000+4)
int n, m;
struct edge {
    int to,w,nex;
};
edge e[M];
int head[N], cnt;
void add_edge(int u, int v, int w) {
    cnt++;
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].nex = head[u];
    head[u] = cnt;
}

struct node {
    int dis,pos;
    // min heap
    bool operator <(const node &x) const {
        return dis > x.dis;
    }
};
int dis[N];
bool seen[N];

void dijkstra(int root) {
    priority_queue<node> pq;
    for (int i = 1; i <= n; ++i) {
        dis[i] = 0x7fffffff;
        seen[i] = false;
    }
    dis[root] = 0;
    pq.push(node{dis[root],root});
    while (!pq.empty()) {
        node nn = pq.top();pq.pop();
        int u = nn.pos;     // 从u出发
        if (seen[u])continue;
        seen[u] = true;
        // 把当前最短路u
        for (int i = head[u]; i != 0; i = e[i].nex) {
            int v = e[i].to;
            if (dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                if (!seen[v])
                    pq.push(node{dis[v], v});
            }
        }
    }
}

int
main()
{
    int u,v,w;
    cin >> n >> m;
    // 本题为带权有向图；
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    // 去的时候是一到多，回来的时候是多到一
    int res = 0;
    // 去每个点
    dijkstra(1);
    for (int i = 2; i <= n; ++i) {
        res += dis[i];
    }
    // 从每个点 回来
    for (int i = 2; i <= n; ++i) {
        dijkstra(i);
        res += dis[1];
    }
    cout << res;
}