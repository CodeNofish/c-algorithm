#include <iostream>
#include <algorithm>
using namespace std;

#define MAX (100*100)
struct node{
    int x,y,w;
};

node nodes[MAX];

bool cmp(node a, node b){
    return a.w < b.w;
}

int pa[MAX];
void init(int n){
    for (int i = 1; i <= n; ++i)
        pa[i] = i;
}
int find(int x) {
    while (x!=pa[x]) {
        pa[x] = pa[pa[x]];
        x = pa[x];
    }
    return x;
}
void merge(int x, int y) {
    int a = find(x), b = find(y);
    if (a != b) pa[a] = b;
}
bool has_common_parent(int x, int y) {
    return find(x) == find(y);
}

/*
 * 这道题所给的数据是矩阵，而矩阵是对称的，我们只需要读入其中一半的数据，就可以转成裸的最小生成树了。
 *
 * 然后使用克鲁斯卡尔算法就可以了。
 *
 * 简单来说 就是把每一条边按权值从小到大排序，然后依次看，如果两个端点不在一个集合里，就把他们合并，计算。
 * 如果已经包含所有点了，直接输出数据退出。
 *
 * Kruskal算法是通过并查集，按照边的权重顺序（从小到大）将边加入生成树中，
 * 但是若加入该边会与生成树形成环则不加入该边,选其次。直到树中含有n - 1条边为止。
 * 时间复杂度：O（E log E）（E为边数）
 */
int
main()
{
    // 注意节点 编号转换
    int n,res = 0;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = i * n + j + 1;
            nodes[idx].x = i + 1;
            nodes[idx].y = j + 1;
            cin >> nodes[idx].w;
        }
    }
    // 0 不用了
    sort(nodes+1, nodes+n*n+1, cmp);
    init(n);
    for (int i = 1; i <= n*n; ++i) {
        if (!has_common_parent(nodes[i].x, nodes[i].y)) {
            // add current edge to res
            merge(nodes[i].x, nodes[i].y);
            res += nodes[i].w;
        }
    }
    cout << res;
}