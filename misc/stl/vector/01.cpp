#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

void
print(vector<int> a)
{
    for_each(a.begin(),a.end(),[](int v){cout<<v<<" ";});
    cout<<endl;
}

int
main()
{
    // create
    vector<int>a;
    vector<int>aa(100);//100个元素 初始值0
    vector<int>aaa(10,6);//10个元素 初始值6
    vector<int>b(a);//b是a的构造复制
    vector<int>bb(aaa.begin()+3,aaa.end()-3);//复制部分区间
    vector<int>bbb[5];//二维

    // add
    a.push_back(5);
    a.insert(a.begin()+1,7);
    a.insert(a.begin()+1,5,10);//插入5个10
    a.insert(a.begin()+1,aaa.begin(),aaa.begin()+3);//插入b的区间
    print(a);

    // 删除
    a.pop_back();
    a.erase(a.begin()+1);//删除指定位置
    print(a);
    a.erase(a.begin()+3,a.end()-3);//删除区间
    print(a);
    a.clear();
    print(a);

    a.resize(5);
    print(a);
}
