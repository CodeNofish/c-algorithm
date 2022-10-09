#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define N (10000+4)
#define M (5*100000+4)
int n,m;
struct edge {
    int to,w,nex;
};
edge e[M];
int head[N], cnt;
int edge_cnt;
inline void add_edge(int u, int v, int w) {
    //
    if (u == v) return;
    for (int i = head[u]; i != 0; i = e[i].nex) {
        if (e[i].to == v) {
            e[i].w = min(e[i].w, w);
            return;
        }
    }
    edge_cnt++;
    //
    cnt++;
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].nex = head[u];
    head[u] = cnt;
}

struct pq_node {
    int dis,pos;
    bool operator <(const pq_node &node) const {
        return dis > node.dis;     // min heap
    }
};
int dis[N];
bool seen[N];
void dijkstra(int root) {
    priority_queue<pq_node> pq;
    for (int i = 1; i <= n; ++i) {
        dis[i] = 0x7fffffff;
        seen[i] = false;
    }
    dis[root] = 0;
    pq.push(pq_node{dis[root], root});
    while (!pq.empty()) {
        pq_node tmp = pq.top();pq.pop();
        int u = tmp.pos, d = tmp.dis;
        if (seen[u]) continue;
        seen[u] = true;
        for (int i = head[u]; i!=0; i = e[i].nex) {
            int v = e[i].to;
            if (dis[v] > dis[u] + e[i].w) {
                dis[v] = dis[u] + e[i].w;
                if (!seen[v])
                    pq.push(pq_node{dis[v], v});
            }
        }
    }
}

int
main()
{
    int s;
    int u,v,w;
    cin >> n >> m >> s;
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }
    m = edge_cnt;
    dijkstra(s);
    for (int i = 1; i <= n; ++i)
        cout << dis[i] << " ";
}