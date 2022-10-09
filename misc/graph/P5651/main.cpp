#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define N (200005)
#define M N<<1
int n, m, Q;

struct edge {
    int to, w, next;
};
edge e[M];
int head[N], cnt;
inline void add_edge(int u, int v, int w) {
    cnt++;
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

/*
w1 xor w2 xor w3 xor w4 = dis[1->4]
w1 xor w2 xor w3 = dis[1->3]
dis[4] xor dis[3] = w4 = dis[3->4]
不存在简单环使得边权异或和不为0
 G中的环（如果存在）边权异或和都为0
 另外，从一条路径增广到另一条路径的必要条件 是这两条路径能够成一个环。
 在这道题中，就是这两条路径的权值 异或和为0
是啊，就是这两条路径相等啊！
 (x,y)之间任一路径权值相等，即所有路径等价。（当然只适用于这道题）

 dis[x] 从root到x的距离都最小（最小生成树）

*/
int dis[N];
bool seen[N];
inline void bfs(int s) {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        dis[i] = 0;
        seen[i] = false;
    }
    q.push(s);
    while (!q.empty()) {
        int u = q.front();q.pop();
        if (seen[u])continue;
        seen[u] = true;
        for (int i = head[u]; i != 0; i = e[i].next) {
            int v = e[i].to;
            if (!seen[v]) {
                dis[v] = dis[u] xor e[i].w;
                q.push(v);
            }
        }
    }
}

// G中的环（如果存在）边权异或和都为 0！
int
main()
{
    int x, y, v;
    cin >> n >> m >> Q;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y >> v;
        add_edge(x, y, v);
        add_edge(y, x, v);
    }
    bfs(1); //bfs预处理出dis来
    for (int i = 1; i <= Q; ++i) {
        cin >> x >> y;
        cout << (dis[x] xor dis[y]) << "\n";
    }
}