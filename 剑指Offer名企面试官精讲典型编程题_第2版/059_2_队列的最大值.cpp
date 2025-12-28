#include <queue>

/**
 * 请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front
 * 的均摊时间复杂度都是O(1)。
 *
 * 若队列为空，pop_front 和 max_value 需要返回 -1。
 *
 * ! 1 <= push_back,pop_front,max_value的总操作数 <= 10000
 * ! 1 <= value <= 10^5
 */

class MaxQueue {
public:
    MaxQueue() {}

    int max_value()
    {
        if (_deque.empty())
            return -1;

        return _deque.front();
    }

    void push_back(int value)
    {
        _queue.push(value);
        while (!_deque.empty() && _deque.back() < value) {
            _deque.pop_back();
        }
        _deque.push_back(value);
    }

    int pop_front()
    {
        if (_queue.empty())
            return -1;

        const int val = _queue.front();
        _queue.pop();
        if (!_deque.empty() && _deque.front() == val) {
            _deque.pop_front();
        }
        return val;
    }

private:
    std::queue<int> _queue; // save raw data
    std::deque<int> _deque; // monotonic decreasing
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */