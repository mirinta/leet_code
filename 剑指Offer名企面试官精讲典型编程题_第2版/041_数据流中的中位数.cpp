#include <queue>

/**
 * 如何得到一个数据流中的中位数？
 *
 * 如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
 *
 * 如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
 *
 * 例如，
 *
 * [2,3,4] 的中位数是 3
 *
 * [2,3] 的中位数是 (2 + 3) / 2 = 2.5
 *
 * 设计一个支持以下两种操作的数据结构：
 *
 * - void addNum(int num) - 从数据流中添加一个整数到数据结构中。
 *
 * - double findMedian() - 返回目前所有元素的中位数。
 *
 * ! 最多会对 addNum、findMedian 进行 50000 次调用。
 *
 * ! 本题与LC 295相同。
 */

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {}

    void addNum(int num)
    {
        // divide elements into two parts, as evenly as possible
        // - if left.size == right.size,
        //   adding to left or right are both ok
        if (left.size() >= right.size()) {
            left.push(num);
            right.push(left.top());
            left.pop();
        } else {
            right.push(num);
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian()
    {
        if (left.size() == right.size())
            return 1.0 * (left.top() + right.top()) / 2;

        return left.size() > right.size() ? left.top() : right.top();
    }

private:
    // [...MAX][MIN...]
    // | LEFT || RIGHT|
    std::priority_queue<int> left;
    std::priority_queue<int, std::vector<int>, std::greater<>> right;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
