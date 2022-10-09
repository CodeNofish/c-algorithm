#include <iostream>
#define N 30005
using namespace std;

int pa[N];
int dis[N]; // 距离栈底的 长度
int cnt[N];

void init() {
    for(int i=1;i<N;++i){
        pa[i]=i;
        dis[i]=0;   // 下面0个方块
        cnt[i]=1;
    }
}

int find(int x){
    if (x == pa[x])
        return x;
    // 根 是栈底
    int fx = pa[x];
    pa[x] = find(fx);
    // 多出来的 未处理的d
    dis[x] += dis[fx];  //当前点到根结点的距离+=父结点到根结点的距离
    return pa[x];
}

// 将包含立方体 X 的堆栈移动到包含立方体 Y 的堆栈顶部。
void merge(int x,int y){
    int a= find(x), b= find(y);
    if(a!=b){
        pa[x]=b;
        dis[a]=cnt[b];      // 新距离
        cnt[b]+=cnt[a];     // b变大
    }
}

int
main()
{
    int p, x, y;
    char m;
    cin>>p;
    init();
    for(int i=0;i<p;++i){
        cin>>m;
        if(m=='M'){
            cin>>x>>y;
            merge(x,y);
        } else if(m=='C'){
            cin>>x;
            find(x);    // 强制更新
            cout << dis[x] << "\n";
        }
    }
    cout<<endl;
}
