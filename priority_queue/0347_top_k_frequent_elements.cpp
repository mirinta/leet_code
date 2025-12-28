#include <queue>
#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return
 * the answer in any order.
 *
 * ! Your algorithm's time complexity must be better than O(nlogn), where n is the array's size.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 * ! k is in the range [1, the number of unique elements in the array].
 * ! It is guaranteed that the answer is unique.
 */

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    std::vector<int> approach2(const std::vector<int>& nums, int k)
    {
        int max = 0;
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
            max = std::max(max, map[val]);
        }
        std::vector<std::vector<int>> bucket(max + 1);
        for (const auto& [val, freq] : map) {
            bucket[freq].push_back(val);
        }
        std::vector<int> result;
        for (int i = bucket.size() - 1; i >= 0 && k > 0; --i) {
            if (bucket[i].empty())
                continue;

            result.insert(result.end(), bucket[i].begin(), bucket[i].end());
            k -= bucket[i].size();
        }
        return result;
    }

    std::vector<int> approach1(const std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        using Pair = std::pair<int, int>;
        auto comparator = [](const auto& p1, const auto& p2) { return p1.second > p2.second; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        for (const auto& [val, freq] : map) {
            pq.emplace(val, freq);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<int> result;
        result.reserve(pq.size());
        while (!pq.empty()) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        return result;
    }
};
