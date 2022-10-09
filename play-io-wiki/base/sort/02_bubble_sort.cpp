#include <iostream>
#include <algorithm>
using namespace std;

// 稳定: 只有相邻交换
// O( n^2 )
void bubble_sort(int arr[], int n) {
    // 较小的元素像是气泡般慢慢「浮」到数列的顶端
    // 每次检查相邻两个元素，如果前面的元素与后面的元素满足给定的排序条件，就将相邻两个元素交换
    bool need_exchange = true;
    while (need_exchange) {
        need_exchange = false;
        for (int i = 0; i < n-1; ++i) {
            if (arr[i] > arr[i+1]) {
                need_exchange = true;
                swap(arr[i], arr[i+1]);
            }
        }
    }
}