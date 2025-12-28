#include <stack>

/**
 * 实现一个MyQueue类，该类用两个栈来实现一个队列。
 *
 * 你只能使用标准的栈操作 -- 也就是只有 push to top, peek/pop from top, size 和 is empty
 * 操作是合法的。
 *
 * 你所使用的语言也许不支持栈。你可以使用 list 或者
 * deque（双端队列）来模拟一个栈，只要是标准的栈操作即可
 *
 * 假设所有操作都是有效的（例如，一个空的队列不会调用 pop 或者 peek 操作）。
 */

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {}

    /** Push element x to the back of queue. */
    void push(int x)
    {
        stack1.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop()
    {
        const int top = peek();
        stack2.pop();
        return top;
    }

    /** Get the front element. */
    int peek()
    {
        process();
        return stack2.top();
    }

    /** Returns whether the queue is empty. */
    bool empty()
    {
        return stack1.empty() && stack2.empty();
    }

private:
    void process()
    {
        if (!stack2.empty())
            return;

        while (!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }

private:
    std::stack<int> stack1;
    std::stack<int> stack2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */