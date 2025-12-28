#include <set>

/**
 * Design a max stack data structure that supports the stack operations and supports finding the
 * stack's maximum element.
 *
 * Implement the MaxStack class:
 *
 * - MaxStack() Initializes the stack object.
 *
 * - void push(int x) Pushes element x onto the stack.
 *
 * - int pop() Removes the element on top of the stack and returns it.
 *
 * - int top() Gets the element on the top of the stack without removing it.
 *
 * - int peekMax() Retrieves the maximum element in the stack without removing it.
 *
 * - int popMax() Retrieves the maximum element in the stack and removes it. If there is more than
 * one maximum element, only remove the top-most one.
 *
 * You must come up with a solution that supports O(1) for each top call and O(logn) for each other
 * call.
 *
 * ! -10^7 <= x <= 10^7
 * ! At most 10^5 calls will be made to push, pop, top, peekMax, and popMax.
 * ! There will be at least one element in the stack when pop, top, peekMax, or popMax is called.
 */

class MaxStack {
public:
    MaxStack() {}

    void push(int x)
    {
        data.emplace(timestamp, x);
        set.emplace(x, timestamp);
        timestamp++;
    }

    int pop()
    {
        const auto [time, val] = *data.rbegin();
        data.erase(std::prev(data.end()));
        set.erase({val, time});
        return val;
    }

    int top()
    {
        return data.rbegin()->second;
    }

    int peekMax()
    {
        return set.rbegin()->first;
    }

    int popMax()
    {
        const auto [val, time] = *set.rbegin();
        set.erase(std::prev(set.end()));
        data.erase({time, val});
        return val;
    }

private:
    int timestamp{0};
    std::multiset<std::pair<int, int>> data; // <timestamp, val>
    std::multiset<std::pair<int, int>> set;  // <val, timestamp>
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */