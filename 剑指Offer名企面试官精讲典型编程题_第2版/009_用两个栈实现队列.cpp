#include <stack>

/**
 * 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail和deleteHead，
 * 分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回-1）
 */

class CQueue {
public:
    CQueue() = default;

    void appendTail(int value)
    {
        m_in.push(value);
    }

    int deleteHead()
    {
        if (m_out.empty() && m_in.empty())
            return -1;

        if (m_out.empty()) {
            while (!m_in.empty()) {
                m_out.push(m_in.top());
                m_in.pop();
            }
        }
        const int val = m_out.top();
        m_out.pop();
        return val;
    }

private:
    std::stack<int> m_in;
    std::stack<int> m_out;
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
