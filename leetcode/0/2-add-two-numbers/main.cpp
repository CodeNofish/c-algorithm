#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr || l2 == nullptr)
            return l1 == nullptr ? l2 : l1;
        ListNode *head, *tail, *p = nullptr;
        int carry = 0, sum = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            sum = carry;
            if (l1 != nullptr) sum += l1->val;
            if (l2 != nullptr) sum += l2->val;
            if (p == nullptr) {
                p = new ListNode(sum % 10);
                head = tail = p;
            }
            else {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            carry = sum / 10;
            l1 = l1 == nullptr ? l1 : l1->next;
            l2 = l2 == nullptr ? l2 : l2->next;
        }
        return head;
    }
};

int
main() {

}