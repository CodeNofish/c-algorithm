#include <iostream>
#include <map>
using namespace std;

#define N 1000

int pa[N+1];
void init(int n){
    for (int i=1;i<=n;++i)
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
    int n,m,k;
    string name, name2;
    map<string, int> idx_map;
    cin>>n>>m;
    for (int i = 0; i < n; ++i) {
        cin >> name;
        idx_map[name] = i+1;
    }
    init(n);
    for (int i = 0; i < m; ++i) {
        cin >> name >> name2;
        int idx1 = idx_map[name];
        int idx2 = idx_map[name2];
        merge(idx1, idx2);
    }
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> name >> name2;
        int idx1 = idx_map[name];
        int idx2 = idx_map[name2];
        if (has_common_parent(idx1, idx2))
            cout << "Yes.\n";
        else
            cout << "No.\n";
    }
}