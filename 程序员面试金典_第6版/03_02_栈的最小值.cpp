#include <stack>

/**
 * 请设计一个栈，除了常规栈支持的pop与push函数以外，还支持min函数，该函数返回栈元素中的最小值。执行push、pop和min操作的时间复杂度必须为O(1)。
 */

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {}

    void push(int x)
    {
        data.push(x);
        min.push(min.empty() ? x : std::min(x, getMin()));
    }

    void pop()
    {
        data.pop();
        min.pop();
    }

    int top()
    {
        return data.top();
    }

    int getMin()
    {
        return min.top();
    }

private:
    std::stack<int> data;
    std::stack<int> min;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */