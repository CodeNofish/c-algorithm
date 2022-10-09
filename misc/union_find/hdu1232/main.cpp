#include <cstdio>
#include <iostream>
using namespace std;

#define MAX_N 1000
int pa[MAX_N];
void init(int n){
    for(int i=0;i<=n;++i)
        pa[i]=i;
}

int find(int x){
    while(x!=pa[x]){
        pa[x]=pa[pa[x]];
        x=pa[x];
    }
    return x;
}

void unions(int x,int y){
    int a= find(x),b= find(y);
    if(a!=b)pa[a]=b;
}

// 计算联通分量个数
int count(int n){
    int res=0;
    for(int i=1;i<=n;++i)
        if(find(i)==i) res++;
    return res;
}

int
main()
{
    for (;;) {
        // 城镇数量N 和 道路数量M
        // 城镇编号为1～ N
        int n, m, p, q;
        int res;
        cin>>n>>m;
        if(n==0)break;

        for(int i=0;i<m;++i){
            cin>>p>>q;
            unions(p,q);
        }
        // 联通全部分量 至少需要的边
        res=count(n)-1;
        cout<<res<<endl;
    }
}