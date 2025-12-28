/**
 * Design your implementation of the linked list. You can choose to use a singly or doubly linked
 * list. A node in a singly linked list should have two attributes: val and next. val is the value
 * of the current node, and next is a pointer/reference to the next node. If you want to use the
 * doubly linked list, you will need one more attribute prev to indicate the previous node in the
 * linked list. Assume all nodes in the linked list are 0-indexed.
 *
 * Implement the MyLinkedList class:
 *
 * - MyLinkedList() Initializes the MyLinkedList object.
 *
 * - int get(int index) Get the value of the indexth node in the linked list. If the index is
 * invalid, return -1.
 *
 * - void addAtHead(int val) Add a node of value val before the first element of the linked list.
 * After the insertion, the new node will be the first node of the linked list.
 *
 * - void addAtTail(int val) Append a node of value val as the last element of the linked list.
 *
 * - void addAtIndex(int index, int val) Add a node of value val before the indexth node in the
 * linked list. If index equals the length of the linked list, the node will be appended to the end
 * of the linked list. If index is greater than the length, the node will not be inserted.
 *
 * - void deleteAtIndex(int index) Delete the indexth node in the linked list, if the index is
 * valid.
 *
 * ! 0 <= index, val <= 1000
 * ! Please do not use the built-in LinkedList library.
 * ! At most 2000 calls will be made to get, addAtHead, addAtTail, addAtIndex and deleteAtIndex.
 */

class MyLinkedList {
public:
    explicit MyLinkedList() : root(new Node(-1)) {}

    ~MyLinkedList()
    {
        auto* node = root;
        while (node) {
            auto* next = node->next;
            delete node;
            node = next;
        }
    }

    int get(int index)
    {
        if (index < 0 || index >= size)
            return -1;

        return getNode(index)->val;
    }

    void addAtHead(int val)
    {
        auto* newHead = new Node(val, root->next);
        root->next = newHead;
        size++;
    }

    void addAtTail(int val)
    {
        auto* tail = size == 0 ? root : getNode(size - 1);
        tail->next = new Node(val);
        size++;
    }

    void addAtIndex(int index, int val)
    {
        if (index < 0 || index > size)
            return;

        auto* prev = index == 0 ? root : getNode(index - 1);
        auto* node = new Node(val, prev->next);
        prev->next = node;
        size++;
    }

    void deleteAtIndex(int index)
    {
        if (index < 0 || index >= size)
            return;

        auto* prev = index == 0 ? root : getNode(index - 1);
        auto* remove = prev->next;
        prev->next = remove->next;
        remove->next = nullptr;
        delete remove;
        size--;
    }

private:
    struct Node {
        int val;
        Node* next;

        explicit Node(int val, Node* next = nullptr) : val(val), next(next) {}
    };

    Node* getNode(int index)
    {
        auto* node = root->next;
        for (int i = 0; i < index; ++i) {
            node = node->next;
        }
        return node;
    }

    int size{0};
    Node* root;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */