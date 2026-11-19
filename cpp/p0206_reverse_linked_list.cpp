// ListNode is supplied by the online judge or the local test harness.
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* following = current->next;
            current->next = previous;
            previous = current;
            current = following;
        }
        return previous;
    }
};
