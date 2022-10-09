#include <iostream>
#include <algorithm>
using namespace std;

#define N 10000
#define M 100000

// ============

struct path{
    int x,y,t;
};
path paths[M+1];
bool cmp(path x, path y){
    return x.t < y.t;
}

// ============
int cnt=0;
int pa[N+1];
void init(int n){
    for(int i=1;i<=n;++i)
        pa[i]=i;
    cnt=n;
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
    if(a!=b){
        pa[a]=b;
        cnt--;
    }
}
bool has_common_parent(int x,int y){
    return find(x)== find(y);
}

// ============

// kruskal 最小生成树
int
main()
{
    int n,m;
    int x,y,t;
    cin>>n>>m;
    for(int i=0;i<m;++i){
        cin>>x>>y>>t;
        paths[i].x = x;
        paths[i].y = y;
        paths[i].t = t;
    }
    sort(paths, paths+m, cmp);

//    for (int i = 0; i < n; ++i) {
//        cout << "(" << paths[i].x << " " << paths[i].y << " " << paths[i].t << ")" << endl;
//    }

    init(n);
    for(int i=0;i<m;++i){
        if(has_common_parent(paths[i].x, paths[i].y)){
            continue;
        } else {
            merge(paths[i].x, paths[i].y);
            if (cnt == 1) {
                cout << paths[i].t;
                return 0;
            }
        }
    }
    cout << -1;
}