#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define N (100000+4)
#define M (200000+4)

struct edge {
    int to, dis, next;
};
edge e[M];
int head[N], cnt;

int dis[N];
bool seen[N];

int n,m,s;

inline void add_edge(int u, int v, int d) {
    cnt++;
    e[cnt].dis = d;
    e[cnt].to = v;
    e[cnt].next = head[u];  // 也从u出发
    head[u] = cnt;
}

struct node {
    int dis, pos;
    // c++ pq 是大顶
    bool operator <(const node &x) const{
        return dis > x.dis;
    }
};

priority_queue<node> q;

inline void dijkstra() {
    dis[s] = 0;
    q.push( node{0, s} );
    while (!q.empty()) {
        node tmp = q.top();q.pop();
        int x = tmp.pos, d = tmp.dis;
        // dis最小 且在V-S中
        if (seen[x]) continue;
        seen[x] = true;
        for (int i=head[x]; i!=0; i=e[i].next) {
            int y = e[i].to;
            // 通过i x->y batter
            if ( dis[y] > dis[x] + e[i].dis ) {
                dis[y] = dis[x] + e[i].dis;
                // y in V-S, push
                if (!seen[y])
                    q.push( node{dis[y], y} );
            }
        }
    }
}

/*
 * 有向边的带非负权图
 */
int
main()
{
    int u,v,w;
    cin >> n >> m >> s;
    for (int i = 1; i <= n; ++i)
        dis[i] = 0x7fffffff;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }
    dijkstra();
    for (int i = 1; i <= n; ++i)
        cout << dis[i] << " ";
}