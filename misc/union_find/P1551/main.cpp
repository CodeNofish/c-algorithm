#include <iostream>
#define MAX 5000
using namespace std;

int pa[MAX];
void init(int n){
    for(int i=1;i<=n;++i)
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
    if(a!=b)pa[a]=b;
}
bool has_common_parent(int x,int y){
    return find(x)== find(y);
}

int
main()
{
    int n,m,p;
    int mi, mj;
    cin>>n>>m>>p;
    init(n);
    for (int i = 0; i < m; ++i) {
        cin>>mi>>mj;
        merge(mi,mj);
    }
    for (int i = 0; i < p; ++i) {
        cin>>mi>>mj;
        if(has_common_parent(mi,mj))
            cout<<"Yes\n";
        else
            cout<<"No\n";
    }
}