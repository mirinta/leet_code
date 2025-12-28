#include <cmath>
#include <list>
#include <vector>

/**
 * Design a queue-like data structure that moves the most recently used element to the end of the
 * queue.
 *
 * Implement the MRUQueue class:
 *
 * - MRUQueue(int n) constructs the MRUQueue with n elements: [1,2,3,...,n].
 *
 * - int fetch(int k) moves the kth element (1-indexed) to the end of the queue and returns it.
 */

class MRUQueue {
public:
    MRUQueue(int n) : bucketSize(std::sqrt(n))
    {
        for (int i = 0; i < n; ++i) {
            data.emplace_back(i + 1);
            if (i % bucketSize == 0) {
                buckets.emplace_back(std::prev(data.end()));
            }
        }
    }

    //  B0   B1   B2   B3
    // +---++---++---++--+
    // |0 1||2 3||4 5||6 |
    // +---++---++---++--+
    //
    // bucket_size = 2
    // if target index = 5,
    // then target bucket = 5 % 2 = B2
    int fetch(int k)
    {
        k--; // to 0-indexed
        const int bucketIndex = k / bucketSize;
        auto iter = buckets[bucketIndex];
        for (int i = 0; i != k % bucketSize; ++i) {
            iter = std::next(iter);
        }
        const int result = *iter;
        data.push_back(result);
        for (int i = bucketIndex + (k % bucketSize != 0); i < buckets.size(); ++i) {
            buckets[i] = std::next(buckets[i]);
        }
        data.erase(iter);
        return result;
    }

private:
    std::list<int> data;
    std::vector<std::list<int>::iterator> buckets;
    const int bucketSize;
};

/**
 * Your MRUQueue object will be instantiated and called as such:
 * MRUQueue* obj = new MRUQueue(n);
 * int param_1 = obj->fetch(k);
 */
