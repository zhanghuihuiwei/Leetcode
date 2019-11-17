#删除链表的第n个节点，就相当于删除链表的第L-n+1个节点，L为链表的长度
#删除完第该节点要接上之后的节点。采取双指针，fast和slow，fast-slow=n
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr || n==0)
        return head;
        ListNode* fast = head, *slow = head;
        while(n--)
        fast = fast->next;
        while(fast->next)
        {
            fast = fast->next;
            slow = slow->next;
        }    
        slow->next = slow->next->next;
        return head; 
    }
};
