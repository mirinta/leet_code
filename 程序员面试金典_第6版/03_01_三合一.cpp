#include <array>
#include <vector>

/**
 * 三合一。描述如何只用一个数组来实现三个栈。
 *
 * 你应该实现push(stackNum,
 * value)、pop(stackNum)、isEmpty(stackNum)、peek(stackNum)方法。stackNum表示栈下标，value表示压入的值。
 *
 * 构造函数会传入一个stackSize参数，代表每个栈的大小。
 *
 * ! 0 <= stackNum <= 2
 */

class TripleInOne {
public:
    TripleInOne(int stackSize)
        : capacity(stackSize), indices{-1, stackSize - 1, 2 * stackSize - 1}, data(3 * stackSize, -1)
    {
    }

    void push(int stackNum, int value)
    {
        if (indices[stackNum] == endIndex(stackNum))
            return;

        data[++indices[stackNum]] = value;
    }

    int pop(int stackNum)
    {
        const int val = peek(stackNum);
        if (val != -1) {
            data[indices[stackNum]--] = -1;
        }
        return val;
    }

    int peek(int stackNum) const
    {
        if (isEmpty(stackNum))
            return -1;

        return data[indices[stackNum]];
    }

    bool isEmpty(int stackNum) const
    {
        return indices[stackNum] < startIndex(stackNum);
    }

private:
    int startIndex(int stackNum) const
    {
        return stackNum * capacity;
    }

    int endIndex(int stackNum) const
    {
        return startIndex(stackNum) + capacity - 1;
    }

private:
    int capacity;
    std::array<int, 3> indices;
    std::vector<int> data;
};

/**
 * Your TripleInOne object will be instantiated and called as such:
 * TripleInOne* obj = new TripleInOne(stackSize);
 * obj->push(stackNum,value);
 * int param_2 = obj->pop(stackNum);
 * int param_3 = obj->peek(stackNum);
 * bool param_4 = obj->isEmpty(stackNum);
 */