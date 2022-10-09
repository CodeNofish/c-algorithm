#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define N (2500+4)
#define M (2*100000+4)
int n,m;

struct edge {int to,w,nex;};
edge e[M<<1];
int head[N],cnt;
inline void add_edge(int u,int v,int w) {
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
int dis[N];
bool seen[N];
void dijkstra(int root) {
    priority_queue<pq_node> pq;
    for (int i = 1; i <= n; ++i) {
        seen[i] = false;
        dis[i] = 0x7fffffff;
    }
    dis[root] = 0;
    pq.push(pq_node{dis[root],root});
    while (!pq.empty()) {
        pq_node tmp = pq.top();pq.pop();
        int u = tmp.pos;
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
    int a,b,c;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a >> b >> c;
        add_edge(a,b,c);
        add_edge(b,a,c);
    }
    dijkstra(1);
    cout << dis[n];
}