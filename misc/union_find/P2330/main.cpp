#include<bits/stdc++.h>//万能头
using namespace std;

/*
 算法1：

题面中有最大值最小，典型的二分！首先二分边权，
 然后把边权小于等于二分的边权的边全部用并查集连接到一起，
 判断是否联通即可。

算法2：

本题要求求的就是瓶颈MST，即最大边权最小的生成树。
 有个定理：一棵最小生成树必定是一棵最小瓶颈生成树。
 所以我们直接做一遍最小生成树即可

 求最大边权最小的生成树，而用克鲁斯卡尔很容易证明这就是最小生成树
 （考虑一下这个算法每次取的都是不构成环的最小边就行了）
 */

#define N 304
#define M 100000
int pa[N];

void init(int n){
    for(int i = 1; i <= n; ++i)
        pa[i]=i;
}
int find(int x){
    while(x!=pa[x]){
        pa[x]=pa[pa[x]];
        x=pa[x];
    }
    return x;
}
void merge(int x,int y){
    int a= find(x),b= find(y);
    if(a!=b) {
        pa[a] = b;
    }
}
bool has_connected(int x,int y){
    return find(x)== find(y);
}

struct Edge {
    int from,to,score;
};
Edge edges[M];
bool operator <(Edge a, Edge b) {
    return a.score < b.score;
}

// n    点集大小
// m    边集大小
void kruskal(int n, int m) {
    int need_edges = 0, max_edge_score = 0;
    sort(edges, edges+m);
    init(n);
    for (int i = 0; i < m; ++i) {
        int x = edges[i].from, y = edges[i].to, s = edges[i].score;
        // 选择边x-y
        if (find(x) != find(y)) {
            pa[find(x)] = find(y);
            need_edges++;
            max_edge_score = max_edge_score > s ?
                    max_edge_score : s;
            if (need_edges >= n-1)
                break;
        }
    }
    cout << need_edges << " " << max_edge_score << endl;
}

int
main()
{
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].from >> edges[i].to >> edges[i].score;
    }
    kruskal(n,m);
}