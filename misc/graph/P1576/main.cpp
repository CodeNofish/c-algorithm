#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define N (2000+4)
#define M (100000+4)

int n,m;
struct edge {
    int to, next;
    double weight;
};
edge e[M<<1];
int head[N], cnt;

inline void add_edge(int u, int v, double w) {
    cnt++;
    e[cnt].to = v;
    e[cnt].weight = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

struct node {
    double weight;
    int pos;
    bool operator <(const node &x) const {
        // 要大顶
        return weight < x.weight;
    }
};

priority_queue<node> q;
double dis[N];
bool seen[N];

void dijkstra(int u) {
    dis[u] = 1.0;
    q.push(node{1.0, u});
    while (!q.empty()) {
        node tmp = q.top();q.pop();
        int x = tmp.pos;
        double d = tmp.weight;
        if (seen[x])continue;
        seen[x] = true;
        for (int i = head[x]; i!=0; i = e[i].next) {
            int y = e[i].to;
            // u->x->y better
            if (dis[y] < dis[x] * e[i].weight) {
                dis[y] = dis[x] * e[i].weight;
                if (!seen[y])
                    q.push(node{dis[y], y});
            }
        }
    }
}



int
main()
{
    int x,y,z;
    int a,b;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y >> z;
        add_edge(x, y, 1.0-double(z)/100.0);
        add_edge(y, x, 1.0-double(z)/100.0);
    }
    cin >> a >> b;
    for (int i = 1; i <= n; ++i)
        dis[i] = 0;
    dis[a] = 1.0;
    dijkstra(a);
    double res = 100.0 / dis[b];
    printf("%.8lf", res);
}