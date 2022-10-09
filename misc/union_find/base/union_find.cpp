
// 初始化 各个集合
void init(int fa[],int n){
    for(int i=0;i<=n;++i)
        fa[i]=i;
}

// 查询集合号
int find(int fa[],int x){
    while(x!=fa[x]) {
        fa[x]=fa[fa[x]];
        x=fa[x];
    }
    return fa[x];
}

// 合并集合号
void unions(int fa[],int x,int y){
    int a=find(fa,x),b= find(fa,y);
    if(a!=b)fa[a]=b;
}

// 计算分量个数
int cnt(int fa[], int n){
    int res=0;
    for(int i=1;i<=n;++i)
        if(i==fa[i])res++;
    return res;
}

// 判断是否在同一分量
bool in_same(int fa[],int x,int y){
    return fa[x]==fa[y];
}