#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


double dist(int x1,int y1,int z1,int x2,int y2,int z2) {
    return (double ) sqrt(pow(x1-x2,2) + pow(y1-y2,2) + pow(z1-z2,2));
}

#define N 1005

int union_find[N];
void init_union_find(int n) {
    for(int i = 1; i <= n; ++i)
        union_find[i] = i;
}
inline int find(int x) {
    while (x != union_find[x]) {
        union_find[x] = union_find[union_find[x]];
        x = union_find[x];
    }
    return x;
}
inline void merge(int x, int y) {
    int a= find(x),b= find(y);
    if(a!=b) union_find[a]=b;
}
inline bool has_connected(int x, int y){
    return find(x) == find(y);
}

int x[N], y[N], z[N];

int
main()
{
    int t;
    int n,h,r;
    cin >> t;
    while (t-- > 0) {
        // 空洞的数量，奶酪的高度和空洞的半径
        cin >> n >> h >> r;
        // 空洞作为初始联通分量，最后逐渐合并
        // n+1 作为底面 和地面计算联通合并
        // n+2 作为顶面 和顶面计算联通合并
        // 最后测试 顶面底面是否联通
        init_union_find(n+2);

        // 需要之前的输入 O(n^2)
        for (int i = 1; i <= n; ++i) {
            cin >> x[i] >> y[i] >> z[i];
            // 先和 顶面地面合并
            if (z[i] <= r)
                merge(i, n+1);
            if (z[i] + r >= h)
                merge(i, n+2);
            //洞间合并
            for (int j = 1; j < i; ++j) {
                if (dist(x[i],y[i],z[i],x[j],y[j],z[j])<=2*r)
                    merge(i, j);
            }
        }
        if (has_connected(n+1, n+2))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}