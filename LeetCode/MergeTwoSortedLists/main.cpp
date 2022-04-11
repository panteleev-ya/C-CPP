#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr && l2 == nullptr) {
            return nullptr;
        }
        int min_;
        ListNode* result_root;
        ListNode* ptr;
        if (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                min_ = l1->val;
                l1 = l1->next;
            }
            else {
                min_ = l2->val;
                l2 = l2->next;
            } // находим начало для нового отсортированного списка
            result_root = new ListNode(min_); // создаем корень нового списка
            ptr = result_root;
            while (l1 != nullptr && l2 != nullptr) { // пока у нас остались не замердженные элементы
                int next_val_;
                if (l1->val < l2->val) {
                    next_val_ = l1->val;
                    l1 = l1->next;
                }
                else {
                    next_val_ = l2->val;
                    l2 = l2->next;
                }
                ptr->next = new ListNode(next_val_);
                ptr = ptr->next;
            }
        }
        else {
            if (l1 != nullptr) {
                min_ = l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                min_ = l2->val;
                l2 = l2->next;
            }
            result_root = new ListNode(min_);
            ptr = result_root;
        }
        while (l1 != nullptr) {
            ptr->next = new ListNode(l1->val);
            l1 = l1->next;
            ptr = ptr->next;
        }
        while (l2 != nullptr) {
            ptr->next = new ListNode(l2->val);
            l2 = l2->next;
            ptr = ptr->next;
        }
        return result_root;
    }
};

ListNode* make_list_node(vector<int> v) {
    if (!v.size()) {
        return nullptr;
    }
    ListNode* root = new ListNode(v[0]);
    ListNode* ptr = root;
    for (int i = 1; i < v.size(); i++) {
        ptr->next = new ListNode(v[i]);
        ptr = ptr->next;
    }
    return root;
}

int32_t main() {
    Solution s1;
    vector <int> v1 = { 1 };
    vector <int> v2 = {};
    ListNode* ln1 = make_list_node(v1);
    ListNode* ln2 = make_list_node(v2);
    ListNode* result = s1.mergeTwoLists(ln1, ln2);
    return 0;
}