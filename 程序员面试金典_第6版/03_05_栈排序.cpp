#include <stack>

/**
 * 栈排序。编写程序，对栈进行排序使最小元素位于栈顶。最多只能使用一个其他的临时栈存放数据，但不得将元素复制到别的数据结构（如数组）中。该栈支持如下操作：push、pop、peek
 * 和 isEmpty。当栈为空时，peek 返回 -1。
 *
 * ! 栈中的元素数目在[0, 5000]范围内。
 */

class SortedStack {
public:
    SortedStack() {}

    void push(int val)
    {
        if (isEmpty() || val <= stack.top()) {
            stack.push(val);
            return;
        }
        std::stack<int> aux;
        while (!stack.empty() && stack.top() < val) {
            aux.push(stack.top());
            stack.pop();
        }
        stack.push(val);
        while (!aux.empty()) {
            stack.push(aux.top());
            aux.pop();
        }
    }

    void pop()
    {
        if (isEmpty())
            return;

        stack.pop();
    }

    int peek()
    {
        if (isEmpty())
            return -1;

        return stack.top();
    }

    bool isEmpty()
    {
        return stack.empty();
    }

private:
    std::stack<int> stack;
};

/**
 * Your SortedStack object will be instantiated and called as such:
 * SortedStack* obj = new SortedStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->isEmpty();
 */