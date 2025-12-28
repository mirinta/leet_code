#include <stack>

/**
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 *
 * Implement the MinStack class:
 *
 * - MinStack() initializes the stack object.
 *
 * - void push(int val) pushes the element val onto the stack.
 *
 * - void pop() removes the element on the top of the stack.
 *
 * - int top() gets the top element of the stack.
 *
 * - int getMin() retrieves the minimum element in the stack.
 *
 * You must implement a solution with O(1) time complexity for each function.
 *
 *
 * ! -2^31 <= val <= 2^31 - 1
 * ! Methods pop, top and getMin operations will always be called on non-empty stacks.
 * ! At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
 */

class MinStack {
public:
    MinStack() = default;

    void push(int val)
    {
        data.push(val);
        if (min.empty()) {
            min.push(val);
        } else {
            min.push(std::min(min.top(), val));
        }
    }

    void pop()
    {
        if (data.empty() || min.empty())
            return;

        data.pop();
        min.pop();
    }

    int top()
    {
        return data.empty() ? INT_MIN : data.top();
    }

    int getMin()
    {
        return min.empty() ? INT_MIN : min.top();
    }

private:
    std::stack<int> data;
    std::stack<int> min;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
