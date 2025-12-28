#include <queue>

/**
 * The median is the middle value in an ordered integer list. If the size of the list is even, there
 * is no middle value, and the median is the mean of the two middle values.
 *
 * - For example, for arr = [2,3,4], the median is 3.
 *
 * - For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
 *
 * Implement the MedianFinder class:
 *
 * - MedianFinder() initializes the MedianFinder object.
 *
 * - void addNum(int num) adds the integer num from the data stream to the data structure.
 *
 * - double findMedian() returns the median of all elements so far. Answers within 10-5 of the
 * actual answer will be accepted.
 *
 * ! -10^5 <= num <= 10^5
 * ! There will be at least one element in the data structure before calling findMedian.
 * ! At most 5 * 104 calls will be made to addNum and findMedian.
 */

class MedianFinder {
public:
    MedianFinder() = default;

    void addNum(int num)
    {
        // add new value to the part with smaller size,
        // (if they have the same size, add new value to right part)
        // and maintain order: any(LEFT) <= any(RIGHT)
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
        // total length % 2 == 0:
        if (left.size() == right.size())
            return 1.0 * (left.top() + right.top()) / 2;

        // total length % 2 != 0:
        return left.size() > right.size() ? left.top() : right.top();
    }

private:
    // Split an array with ascending order into two parts:
    // [...MAX][MIN...]
    // | LEFT || RIGHT|
    // where |LEFT.size() - RIGHT.size()| <= 1,
    // any element in the RIGHT part >= any element in the LEFT part
    std::priority_queue<int, std::vector<int>, std::greater<>> right;
    std::priority_queue<int> left;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
