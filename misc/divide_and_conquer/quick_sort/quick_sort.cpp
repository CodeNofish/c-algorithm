#include <iostream>

// 分解  取出基准元素 和基准元素比较大小 分为两个序列排序
// 求解子问题 对子序列快排
// 合并 合并基准元素和两个有序子序列

// 选取基准元素 ?
// 取第一个元素；
// 取最后一个元素；
// 取中间位置的元素；
// 取第一个元素、最后一个元素、中间位置的元素三者的中位数；
// 取第一个元素和最后一个元素之间位置的随机数 k （low≤ k ≤high），选R[ k ]作为基准元素。
inline void swap(int arr[], int x, int y) {
    if (arr[x] != arr[y]) {
        arr[x] ^= arr[y];
        arr[y] ^= arr[x];
        arr[x] ^= arr[y];
    }
}

int partition(int arr[], int l, int h) {
    int i=l,j=h;
    int p=l+rand()%(h-l+1);
    swap(arr,l,p);
    int pivot=arr[l];
    while(i<j){
        // skip matched element
        while(i<j&&arr[j]>pivot)j--;
        // swap unmatched element
        if(i<j)swap(arr,i++,j);
        while(i<j&&arr[i]<pivot)i++;
        if(i<j)swap(arr,i,j--);
    }
    return i;   // return mid
}

// 减少交换次数
int partition2(int arr[],int l,int h){
    int i=l,j=h;
    swap(arr,l,l+rand()%(h-l+1));
    int pivot=arr[l];
    while(i<j){
        // 找出两个符合条件的
        while(i<j&&arr[j]>pivot)j--;
        while (i<j&&arr[i]<=pivot)i++;
        if(i<j)swap(arr,i++,j--);
    }
    // 交换左边的
    if(arr[i]>pivot){
        swap(arr,i-1,l);
        return i-1;
    }
    // arr[i] <= pivot
    swap(arr,i,l);
    return i;
}

void quick_sort(int arr[], int l, int h) {
    if (l<h){
        int m = partition2(arr,l,h);
        quick_sort(arr,l,m-1);
        quick_sort(arr,m+1,h);
    }
}

int
main()
{
    int w[] = {4,10,7,11,3,5,14,2};
    int n = sizeof(w) / sizeof(int);
    quick_sort(w, 0, n-1);
    for (int i = 0; i < n; ++i)
        std::cout << w[i] << std::endl;
}