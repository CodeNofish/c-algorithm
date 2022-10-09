#include <iostream>

using namespace std;

#define MAX_N 10000
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

void merge(int x,int y){
    int a= find(x),b= find(y);
    if(a!=b)pa[a]=b;
}

int
main()
{
    int n,m,z,x,y;
    cin>>n>>m;
    init(n);
    for(int i=0;i<m;++i){
        cin>>z>>x>>y;
        if(z==1){
            merge(x,y);
        } else if(z==2){
            if(find(x)== find(y))
                cout<<"Y\n";
            else
                cout<<"N\n";
        }
    }
    cout<<endl;
}