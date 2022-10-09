#include <iostream>

using namespace std;
#define Maxsize 100

template<typename ElemType>
struct node {
    ElemType data;
    struct node *next;
};

//template<typename ElemType>
//node<ElemType>* make_linked_list() {
//    auto arr = new array_list<ElemType>;
//    arr->length = 0;
//    return arr;
//}
//
//template<typename ElemType>
//void delete_array_list(array_list<ElemType> *L) {
//    delete L;
//}

template<typename ElemType>
bool insert(node<ElemType> *L, int idx, ElemType e) {
    node<ElemType> *p = L, *prev = nullptr;
    for (int i = 0; i < idx; ++i) {
        if (p== nullptr)    return false;
        prev = p;
        p = p->next;
    }
    auto new_node = new node<ElemType>{e, nullptr};
    if (prev!= nullptr) prev->next = new_node;
    new_node->next = p;
    return true;
}

//template<typename ElemType>
//bool remove(array_list<ElemType> &L, int idx, ElemType &e) {
//    if (idx<0||idx>L.length)    return false;
//    e = L.data[idx];
//    for (int i = idx; i< L.length-1;++i){
//        L.data[i] = L.data[i+1];
//    }
//    L.length--;
//    return true;
//}

int
main()
{
//    auto list = make_array_list<int>();
//    for (int i = 0; i < list->length; ++i)
//        cout<<list->data[i]<<" ";
//    cout<<endl;

    node<int> *list;

    insert(list, 0, 1);
    insert(list, 0, 2);

    for (auto p = list; p!= nullptr; p=p->next)
        cout<<list->data<<" ";
    cout<<endl;

//    int removed;
//    remove(*list, 0, removed);
//    for (int i = 0; i < list->length; ++i)
//        cout<<list->data[i]<<" ";
//    cout<<endl;

//    delete_array_list(list);
}