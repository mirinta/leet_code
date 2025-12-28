#include <vector>

/**
 * Design a stack that supports increment operations on its elements.
 *
 * Implement the CustomStack class:
 *
 * - CustomStack(int maxSize) Initializes the object with maxSize which is the maximum number of
 * elements in the stack.
 *
 * - void push(int x) Adds x to the top of the stack if the stack has not reached the maxSize.
 *
 * - int pop() Pops and returns the top of the stack or -1 if the stack is empty.
 *
 * - void inc(int k, int val) Increments the bottom k elements of the stack by val. If there are
 * less than k elements in the stack, increment all the elements in the stack.
 *
 * ! 1 <= maxSize, x, k <= 1000
 * ! 0 <= val <= 100
 * ! At most 1000 calls will be made to each method of increment, push and pop each separately.
 */

class CustomStack {
public:
    CustomStack(int maxSize) : capacity(maxSize) {}

    void push(int x)
    {
        if (data.size() == capacity)
            return;

        data.emplace_back(x, 0);
    }

    int pop()
    {
        if (data.empty())
            return -1;

        const auto [value, diff] = data.back();
        data.pop_back();
        if (!data.empty()) {
            data.back().second += diff;
        }
        return value + diff;
    }

    void increment(int k, int val)
    {
        const int size = std::min<int>(k, data.size());
        if (size > 0) {
            data[size - 1].second += val;
        }
    }

private:
    int capacity;
    std::vector<std::pair<int, int>> data; // <value, diff>
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */