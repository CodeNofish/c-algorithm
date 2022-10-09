#include <iostream>

using namespace std;
// merge arr[l..m] arr[m+1, h]
void merge(int arr[], int l, int m, int h) {
    auto size = h-l+1;
    auto buf = new int[size];
    int i=l, j=m+1, idx=0;
    while (i<=m&&j<=h)
        buf[idx++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
    while (i<=m)
        buf[idx++] = arr[i++];
    while (j<=h)
        buf[idx++] = arr[j++];
    idx = 0;
    while (idx < size)
        arr[l+idx++] = buf[idx];
    delete[] buf;
}

void merge_sort(int arr[], int l, int h) {
    if (l<h) {
        int m=(l+h)>>1;
        merge_sort(arr,l,m);
        merge_sort(arr,m+1,h);
        merge(arr,l,m,h);
    }
}

int
main()
{
    int w[] = {4,10,7,11,3,5,14,2};
    int n = sizeof(w) / sizeof(int);
    merge_sort(w, 0, n-1);
    for (int i = 0; i < n; ++i)
        cout << w[i] << endl;
}