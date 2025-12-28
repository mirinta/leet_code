#include <queue>
#include <vector>

/**
 * Design a class to find the kth largest element in a stream. Note that it is the kth largest
 * element in the sorted order, not the kth distinct element.
 *
 * Implement KthLargest class:
 *
 * - KthLargest(int k, int[] nums) initializes the object with the integer k and the stream of
 * integers nums.
 *
 * - int add(int val) appends the integer val to the stream and returns the element representing the
 * kth largest element in the stream.
 *
 * ! 1 <= k
 * ! 0 <= nums.length
 * ! There will be at least k elements in the array when you search for the kth element.
 */

class KthLargest {
public:
    KthLargest(int k, std::vector<int>& nums) : k(k)
    {
        for (const auto& val : nums) {
            add(val);
        }
    }

    int add(int val)
    {
        pq.push(val);
        if (pq.size() > k) {
            pq.pop();
        }
        return pq.top();
    }

private:
    int k;
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
