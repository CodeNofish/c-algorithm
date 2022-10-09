#include <iostream>
#include <algorithm>
using namespace std;

// 由于 swap（交换两个元素）操作的存在，选择排序是一种不稳定的排序算法。
// 不稳定 O( n^2 )
void selection_sort(int arr[], int n) {
    // 模拟扑克牌排序 往后选择最小的,放到应该的位置
    for (int i = 0; i < n; ++i) {
        int select = i;
        for (int j = i; j < n; ++j) {
            if (arr[j] < select)
                select = j;
        }
        swap(arr[i], arr[select]);
    }
}