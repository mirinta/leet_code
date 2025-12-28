#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

/**
 * The problem involves tracking the frequency of IDs in a collection that changes over time. You
 * have two integer arrays, nums and freq, of equal length n. Each element in nums represents an ID,
 * and the corresponding element in freq indicates how many times that ID should be added to or
 * removed from the collection at each step.
 *
 * - Addition of IDs: If freq[i] is positive, it means freq[i] IDs with the value nums[i] are added
 * to the collection at step i.
 *
 * - Removal of IDs: If freq[i] is negative, it means -freq[i] IDs with the value nums[i] are
 * removed from the collection at step i.
 *
 * Return an array ans of length n, where ans[i] represents the count of the most frequent ID in the
 * collection after the ith step. If the collection is empty at any step, ans[i] should be 0 for
 * that step.
 *
 * ! 1 <= nums.length == freq.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! -10^5 <= freq[i] <= 10^5
 * ! freq[i] != 0
 * ! The input is generated such that the occurrences of an ID will not be negative in any step.
 */

class Solution {
public:
    std::vector<long long> mostFrequentIDs(std::vector<int>& nums, std::vector<int>& freq)
    {
        return approach2(nums, freq);
    }

private:
    std::vector<long long> approach2(const std::vector<int>& nums, const std::vector<int>& freq)
    {
        const int n = nums.size();
        std::unordered_map<int, long long> map;
        using Pair = std::pair<long long, int>;
        std::priority_queue<Pair, std::vector<Pair>, std::less<>> pq;
        std::vector<long long> result(n);
        for (int i = 0; i < n; ++i) {
            map[nums[i]] += freq[i];
            pq.emplace(map[nums[i]], nums[i]);
            while (pq.top().first != map[pq.top().second]) {
                pq.pop();
            }
            result[i] = pq.top().first;
        }
        return result;
    }

    std::vector<long long> approach1(const std::vector<int>& nums, const std::vector<int>& freq)
    {
        const int n = nums.size();
        std::unordered_map<int, long long> map;
        std::set<std::pair<long long, int>, std::greater<>> set;
        std::vector<long long> result(n);
        for (int i = 0; i < n; ++i) {
            const int id = nums[i];
            const long long delta = freq[i];
            auto iter = set.find({map[id], id});
            if (iter != set.end()) {
                set.erase(iter);
            }
            map[id] += delta;
            set.emplace(map[id], id);
            result[i] = set.begin()->first;
        }
        return result;
    }
};