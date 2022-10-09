#include <iostream>

using namespace std;
#define Maxsize 100

template<typename ElemType>
struct array_list {
    ElemType data[Maxsize];
    int length;
};

template<typename ElemType>
array_list<ElemType>* make_array_list() {
    auto arr = new array_list<ElemType>;
    arr->length = 0;
    return arr;
}

template<typename ElemType>
void delete_array_list(array_list<ElemType> *L) {
    delete L;
}

template<typename ElemType>
bool insert(array_list<ElemType> &L, int idx, ElemType e) {
    if (idx<0||idx>L.length)    return false;
    if (L.length==Maxsize)  return false;
    for (int i = L.length; i > idx; i--) {
        L.data[i] = L.data[i-1];
    }
    L.data[idx] = e;
    L.length++;
    return true;
}

template<typename ElemType>
bool remove(array_list<ElemType> &L, int idx, ElemType &e) {
    if (idx<0||idx>L.length)    return false;
    e = L.data[idx];
    for (int i = idx; i< L.length-1;++i){
        L.data[i] = L.data[i+1];
    }
    L.length--;
    return true;
}

int
main()
{
    auto list = make_array_list<int>();
    for (int i = 0; i < list->length; ++i)
        cout<<list->data[i]<<" ";
    cout<<endl;


    insert(*list, 0, 1);
    insert(*list, 0, 2);
    for (int i = 0; i < list->length; ++i)
        cout<<list->data[i]<<" ";
    cout<<endl;

    int removed;
    remove(*list, 0, removed);
    for (int i = 0; i < list->length; ++i)
        cout<<list->data[i]<<" ";
    cout<<endl;

    delete_array_list(list);
}