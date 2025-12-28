#include <stack>

/**
 * Implement a first in first out queue using only two stacks. The implemented queue should support
 * all the functions of a normal queue (push, peek, pop, and empty).
 *
 * Implement the MyQueue class:
 *
 * - void push(int x) pushes element x to the back of the queue.
 *
 * - int pop() removes the element from the front of the queue and returns it.
 *
 * - int peek() returns the element at the front of the queue.
 *
 * - boolean empty() returns true if the queue is empty, false otherwise.
 *
 * Notes:
 *
 * - You must use only standard operations of a stack, which means only push to top, peek/pop from
 * top, size, and is empty operations are valid.
 *
 * - Depending on your language, the stack may not be supported natively. You may simulate a stack
 * using a list or deque as long as you use only a stack's standard operations.
 *
 * ! 1 <= x <= 9
 * ! At most 100 calls will be made to push, pop, peek, and empty.
 * ! All the calls to pop and peek are valid.
 */

class MyQueue {
public:
    MyQueue() {}

    void push(int x)
    {
        in.push(x);
    }

    int pop()
    {
        if (empty())
            return -1;

        const int result = peek();
        out.pop();
        return result;
    }

    int peek()
    {
        if (empty())
            return -1;

        process();
        return out.top();
    }

    bool empty()
    {
        return in.empty() && out.empty();
    }

private:
    void process()
    {
        if (!out.empty())
            return;

        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }

private:
    std::stack<int> in;
    std::stack<int> out;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
