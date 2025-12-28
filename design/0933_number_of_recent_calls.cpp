#include <queue>
#include <vector>

/**
 * You have a RecentCounter class which counts the number of recent requests within a certain time
 * frame.
 *
 * Implement the RecentCounter class:
 *
 * - RecentCounter() Initializes the counter with zero recent requests.
 *
 * - int ping(int t) Adds a new request at time t, where t represents some time in milliseconds, and
 * returns the number of requests that has happened in the past 3000 milliseconds (including the new
 * request). Specifically, return the number of requests that have happened in the inclusive range
 * [t - 3000, t].
 *
 * It is guaranteed that every call to ping uses a strictly larger value of t than the
 * previous call.
 *
 * ! 1 <= t <= 10^9
 * ! Each test case will call ping with strictly increasing values of t.
 * ! At most 10^4 calls will be made to ping.
 */

class RecentCounter {
public:
    RecentCounter() {}

    int ping(int t)
    {
        return approach2(t);
    }

private:
    // approach2: queue
    std::queue<int> _queue;
    int approach2(int t)
    {
        _queue.push(t);
        while (!_queue.empty() && _queue.front() < t - 3000) {
            _queue.pop();
        }
        return _queue.size();
    }

    // approach1: vector + binary search
    // store all data, may be inefficient
    std::vector<int> _vec;
    int approach1(int t)
    {
        _vec.push_back(t);
        // find the first element >= t - 3000
        auto lower = std::lower_bound(_vec.begin(), _vec.end(), t - 3000);
        // find the first element > t
        auto upper = std::upper_bound(_vec.begin(), _vec.end(), t);
        return std::distance(lower, upper);
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */