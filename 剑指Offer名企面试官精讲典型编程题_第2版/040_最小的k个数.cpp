#include <queue>
#include <vector>

/**
 * 输入整数数组 arr ，找出其中最小的 k 个数。
 *
 * 例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。
 *
 * ! 0 <= k <= arr.length <= 10000
 * ! 0 <= arr[i] <= 10000
 */

class Solution {
public:
    std::vector<int> getLeastNumbers(std::vector<int>& arr, int k)
    {
        if (k <= 0)
            return {};

        if (k >= arr.size())
            return arr;

        std::priority_queue<int> pq;
        for (const auto& val : arr) {
            pq.push(val);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top());
            pq.pop();
        }
        return result;
    }
};