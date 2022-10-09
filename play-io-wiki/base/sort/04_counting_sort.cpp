#include <iostream>
#include <algorithm>
#include <memory>
#include <cstring>

using namespace std;

// 一种线性时间的排序算法。
//
// 计数排序的工作原理是使用一个额外的数组 ，
// 其中第  个元素是待排序数组  中值等于  的元素的个数，
// 然后根据数组  来将  中的元素排到正确的位置。
//
// 计数排序是一种稳定的排序算法。
//
//计算每个数出现了几次；
//求出每个数出现次数的 前缀和；
//利用出现次数的前缀和，从右至左计算每个数的排名。
#define N 100010
#define W 100010
int w, cnt[W], b[N];
void counting_sort(int arr[], int n) {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; ++i)
        cnt[arr[i]]++;
    //  w代表待排序数据的值域大小
    for (int i = 0; i < w; ++i)
        cnt[i] += cnt[i-1];
    for (int i = n-1; i >= 0; --i)
        b[ cnt[arr[i]]-- ] = arr[i];

    // 计数前缀和, 成为顺序序列
}