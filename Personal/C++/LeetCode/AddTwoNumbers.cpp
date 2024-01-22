#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr){};
    ListNode(int x) : val(x), next(nullptr){};
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *l1 = new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9)))))));
ListNode *l2 = new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9))));
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2);

int main(int argc, char const *argv[])
{
    ListNode *tmp = addTwoNumbers(l1, l2);

    ListNode *current = tmp;

    int j = 1;

    while (current != nullptr)
    {
        std::cout << current->val << ", " << std::endl;
        current = current->next;
        j++;
    }
    return 0;
}

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{

    ListNode *res = nullptr;

    int tmp, carry = 0;

    while (l1 != nullptr && l2 != nullptr)
    {
        tmp = carry + l1->val + l2->val;
        res = new ListNode(tmp % 10, res);
        carry = floor(tmp / 10);
        l1 = l1->next;
        l2 = l2->next;
    }

    while (l1 != nullptr)
    {
        tmp = carry + l1->val;
        res = new ListNode(tmp % 10, res);
        carry = floor(tmp / 10);
        l1 = l1->next;
    }

    while (l2 != nullptr)
    {
        tmp = carry + l2->val;
        res = new ListNode(tmp % 10, res);
        carry = floor(tmp / 10);
        l2 = l2->next;
    }

    if (carry != 0)
        res = new ListNode(1, res);

    l1 = nullptr;

    while (res != nullptr)
    {
        l1 = new ListNode(res->val, l1);
        res = res->next;
    }

    return l1;
}