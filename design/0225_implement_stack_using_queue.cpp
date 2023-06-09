#include <queue>

/**
 * Implement a last-in-last-out stack using only two queues. The implemented stack should support
 * all the functions a normal stack (push, top, pop, and empty).
 *
 * Implement the MyStack class:
 *
 * - void push(int x) pushes element x to the top of the stack.
 *
 * - int pop() removes the element on the top of teh stack and returns it.
 *
 * - int top() return the element on the top of the stack.
 *
 * - boolean empty() returns true if the stack is empty, false otherwise.
 *
 * Note:
 *
 * - You must use only standard operations of a queue, which means that only push to back, peek/top
 * from front, size and is empty operations are valid.
 *
 * - Depending on your language, the queue may not be supported natively. You may simulate a queue
 * using a list or deque as long as you use only a queue's standard operations.
 */

class MyStack
{
public:
    MyStack() {}

    void push(int x)
    {
        const auto size = queue.size();
        queue.push(x);
        for (size_t i = 0; i < size; ++i) {
            const auto val = queue.front();
            queue.pop();
            queue.push(val);
        }
    }

    int pop()
    {
        const auto val = queue.front();
        queue.pop();
        return val;
    }

    int top() { return queue.front(); }

    bool empty() { return queue.empty(); }

private:
    std::queue<int> queue;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */