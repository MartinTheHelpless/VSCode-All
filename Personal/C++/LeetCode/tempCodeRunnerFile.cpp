
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