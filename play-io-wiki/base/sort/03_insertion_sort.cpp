#include <iostream>
#include <algorithm>
using namespace std;

// 插入排序是一种稳定的排序算法。
//
//插入排序的最优时间复杂度为 ，在数列几乎有序时效率很高。
//插入排序的最坏时间复杂度和平均时间复杂度都为 。
void insertion_sort(int arr[], int n) {
    // 将待排列元素划分为「已排序」和「未排序」两部分，
    // 每次从「未排序的」元素中选择一个插入到「已排序的」元素中的正确位置。

    // 左边 已经排序好, 往左边相邻交换
    for (int i = 1; i < n; ++i) {
        int key = arr[i];       // 本次扩充的元素
        int j = i-1;          // 左边的元素
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}