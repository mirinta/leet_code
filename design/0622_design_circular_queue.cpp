#include <vector>

/**
 * Design your implementation of the circular queue. The circular queue is a linear data structure
 * in which the operations are performed based on FIFO (First In First Out) principle, and the last
 * position is connected back to the first position to make a circle. It is also called "Ring
 * Buffer".
 *
 * One of the benefits of the circular queue is that we can make use of the spaces in front of the
 * queue. In a normal queue, once the queue becomes full, we cannot insert the next element even if
 * there is a space in front of the queue. But using the circular queue, we can use the space to
 * store new values.
 *
 * Implement the MyCircularQueue class:
 *
 * - MyCircularQueue(k) Initializes the object with the size of the queue to be k.
 *
 * - int Front() Gets the front item from the queue. If the queue is empty, return -1.
 *
 * - int Rear() Gets the last item from the queue. If the queue is empty, return -1.
 *
 * - boolean enQueue(int value) Inserts an element into the circular queue. Return true if the
 * operation is successful.
 *
 * - boolean deQueue() Deletes an element from the circular queue. Return true if the operation is
 * successful.
 *
 * - boolean isEmpty() Checks whether the circular queue is empty or not.
 *
 * - boolean isFull() Checks whether the circular queue is full or not.
 *
 * ! You must solve the problem without using the built-in queue data structure.
 *
 * ! 1 <= k <= 1000
 * ! 0 <= value <= 1000
 * ! At most 3000 calls will be made to enQueue, deQueue, Front, Rear, isEmpty, and isFull.
 */

class MyCircularQueue {
public:
    explicit MyCircularQueue(int k) : _capacity(k), _queue(k, 0) {}

    bool enQueue(int value)
    {
        if (isFull())
            return false;

        // [] x x, count = 2, capacity = 3
        //    ^
        //    current head
        _queue[(_headIndex + _count) % _capacity] = value;
        _count++;
        return true;
    }

    bool deQueue()
    {
        if (isEmpty())
            return false;

        // x x [x], count = 3, capacity = 3
        //   ^  ^ new head
        //   current head
        _headIndex = (_headIndex + 1) % _capacity;
        _count--;
        return true;
    }

    int Front()
    {
        if (isEmpty())
            return -1;

        return _queue[_headIndex];
    }

    int Rear()
    {
        if (isEmpty())
            return -1;

        // [x]   x   x, count = 3, capacity = 3
        //  ^    ^
        //  tail head
        return _queue[(_headIndex + _count - 1) % _capacity];
    }

    bool isEmpty() const
    {
        return _count == 0;
    }

    bool isFull() const
    {
        return _count == _capacity;
    }

private:
    int _headIndex{0};
    int _count{0}; // actual size
    int _capacity; // max size
    std::vector<int> _queue;
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
