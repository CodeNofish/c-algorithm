#include <iostream>
#include <algorithm>
using namespace std;

#define N 10004
#define M 20000

struct Edge {
    int from,to,score;
};
bool operator <(Edge a, Edge b) {
    return a.score < b.score;
}
Edge edges[M];

int pa[N];
void init(int n) {
    for (int i = 1; i <= n; ++i)
        pa[i] = i;
}
int find(int x) {
    while (x != pa[x]) {
        pa[x] = pa[pa[x]];
        x = pa[x];
    }
    return x;
}
void merge(int x, int y) {
    int a = find(x), b = find(y);
    pa[a] = b;
}
bool merged(int x, int y) {
    return find(x) == find(y);
}

/*
 * 多重图, 但我只要最大权的边
 * 求的不是 最短路径，因为不是累积权值最小，而是经过路径的最大权值
 * 判断联通s和t的路径，
 */
int
main()
{
    int n,m,s,t;
    int u,v,w;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].from >> edges[i].to >> edges[i].score;
    }
    init(n);
    sort(edges, edges + m);
    for (int i = 0; i < m; ++i) {
        merge(edges[i].from, edges[i].to);
        if (merged(s, t)) {
            cout << edges[i].score;     // 已经排序了
            break;
        }
    }
}