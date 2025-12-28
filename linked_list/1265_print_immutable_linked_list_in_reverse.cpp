/**
 * This is the ImmutableListNode's API interface.
 * You should not implement it, or speculate about its implementation.
 */
class ImmutableListNode {
public:
    void printValue();            // print the value of the node.
    ImmutableListNode* getNext(); // return the next node.
};

/**
 * You are given an immutable linked list, print out all values of each node in reverse with the
 * help of the following interface:
 *
 * - ImmutableListNode: An interface of immutable linked list, you are given the head of the list.
 *
 * You need to use the following functions to access the linked list (you can't access the
 * ImmutableListNode directly):
 *
 * - ImmutableListNode.printValue(): Print value of the current node.
 *
 * - ImmutableListNode.getNext(): Return the next node.
 *
 * The input is only given to initialize the linked list internally. You must solve this problem
 * without modifying the linked list. In other words, you must operate the linked list using only
 * the mentioned APIs.
 *
 * ! The length of the linked list is between [1, 1000].
 * ! The value of each node in the linked list is between [-1000, 1000].
 */

class Solution {
public:
    void printLinkedListInReverse(ImmutableListNode* head)
    {
        return approach2(head);
    }

private:
    // time O(N^2), space O(1)
    void approach2(ImmutableListNode* head)
    {
        // HEAD X X X X X TAIL NULL
        ImmutableListNode* current = nullptr;
        ImmutableListNode* target = nullptr;
        while (head != target) {
            current = head;
            while (current->getNext() != target) {
                current = current->getNext();
            }
            current->printValue();
            target = current;
        }
    }

    // recursive, time O(N), space O(N)
    void approach1(ImmutableListNode* head)
    {
        if (!head)
            return;

        approach1(head->getNext());
        head->printValue();
    }
};