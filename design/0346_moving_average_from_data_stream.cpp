#include <queue>

/**
 * Given a stream of integers and a window size, calculate the moving average of all integers in the
 * sliding window.
 *
 * Implement the MovingAverage class:
 *
 * - MovingAverage(int size) Initializes the object with the size of the window size.
 *
 * - double next(int val) Returns the moving average of the last size values of the stream.
 *
 * ! 1 <= size <= 1000
 * ! -10^5 <= val <= 10^5
 * ! At most 10^4 calls will be made to next.
 */

class MovingAverage {
public:
    MovingAverage(int size) : capacity(size) {}

    double next(int val)
    {
        sum += val;
        deque.push_back(val);
        if (deque.size() > capacity) {
            sum -= deque.front();
            deque.pop_front();
        }
        return sum / deque.size();
    }

private:
    int capacity;
    double sum{0};
    std::deque<int> deque;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
