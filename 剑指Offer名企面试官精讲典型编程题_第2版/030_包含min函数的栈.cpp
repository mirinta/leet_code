#include <stack>

/**
 * 定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及
 * pop 的时间复杂度都是 O(1)。
 *
 * ! 本题与LC 155相同。
 */

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {}

    void push(int x)
    {
        _data.push(x);
        if (_min.empty() || x < min()) {
            _min.push(x);
        } else {
            _min.push(min());
        }
    }

    void pop()
    {
        _data.pop();
        _min.pop();
    }

    int top()
    {
        return _data.top();
    }

    int min()
    {
        return _min.top();
    }

private:
    std::stack<int> _data;
    std::stack<int> _min;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */