#include <memory>

/**
 * Design your implementation of the circular double-ended queue (deque).
 *
 * Implement the MyCircularDeque class:
 *
 * - MyCircularDeque(int k) Initializes the deque with a maximum size of k.
 *
 * - boolean insertFront() Adds an item at the front of Deque. Returns true if the operation is
 * successful, or false otherwise.
 *
 * - boolean insertLast() Adds an item at the rear of Deque. Returns true if the operation is
 * successful, or false otherwise.
 *
 * - boolean deleteFront() Deletes an item
 * from the front of Deque. Returns true if the operation is successful, or false otherwise.
 *
 * - boolean deleteLast() Deletes an item from the rear of Deque. Returns true if the operation is
 * successful, or false otherwise.
 *
 * - int getFront() Returns the front item from the Deque. Returns -1 if the deque is empty.
 *
 * - int getRear() Returns the last item from Deque. Returns -1 if the deque is empty.
 *
 * - boolean isEmpty() Returns true if the deque is empty, or false otherwise.
 *
 * - boolean isFull() Returns true if the deque is full, or false otherwise.
 *
 * ! 1 <= k <= 1000
 * ! 0 <= value <= 1000
 * ! At most 2000 calls will be made to insertFront, insertLast, deleteFront, deleteLast, getFront,
 * ! getRear, isEmpty, isFull.
 */

class MyCircularDeque {
public:
    explicit MyCircularDeque(int k) : capacity(k), head(std::make_shared<Node>(-1)), tail(std::make_shared<Node>(-1))
    {
        head->next = tail;
        tail->prev = head;
    }

    bool insertFront(int value)
    {
        if (isFull())
            return false;

        auto node = std::make_shared<Node>(value);
        auto first = head->next;
        head->next = node;
        node->next = first;
        node->prev = head;
        first->prev = node;
        size++;
        return true;
    }

    bool insertLast(int value)
    {
        if (isFull())
            return false;

        auto node = std::make_shared<Node>(value);
        auto last = tail->prev;
        last.lock()->next = node;
        node->prev = last;
        node->next = tail;
        tail->prev = node;
        size++;
        return true;
    }

    bool deleteFront()
    {
        if (isEmpty())
            return false;

        auto next = head->next->next;
        head->next = next;
        next->prev = head;
        size--;
        return true;
    }

    bool deleteLast()
    {
        if (isEmpty())
            return false;

        auto prev = tail->prev.lock()->prev.lock();
        prev->next = tail;
        tail->prev = prev;
        size--;
        return true;
    }

    int getFront()
    {
        if (isEmpty())
            return -1;

        return head->next->val;
    }

    int getRear()
    {
        if (isEmpty())
            return -1;

        return tail->prev.lock()->val;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    bool isFull() const
    {
        return size == capacity;
    }

private:
    struct Node {
        int val;
        std::weak_ptr<Node> prev;
        std::shared_ptr<Node> next;

        explicit Node(int val) : val(val) {}
    };

    int size{0};
    int capacity;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */