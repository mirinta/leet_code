#include <set>
#include <unordered_map>
#include <vector>

/**
 * You are given an array nums of n integers and two integers k and x.
 *
 * The x-sum of an array is calculated by the following procedure:
 *
 * - Count the occurrences of all elements in the array.
 *
 * - Keep only the occurrences of the top x most frequent elements. If two elements have the same
 * number of occurrences, the element with the bigger value is considered more frequent.
 *
 * - Calculate the sum of the resulting array. Note that if an array has less than x distinct
 * elements, its x-sum is the sum of the array.
 *
 * Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray
 * nums[i..i + k - 1].
 *
 * ! nums.length == n
 * ! 1 <= n <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= x <= k <= nums.length
 */

class Container
{
public:
    explicit Container(long long x) : x(x) {}

    void insert(long long val)
    {
        if (map.count(val)) {
            remove({map[val], val});
        }
        map[val]++;
        insert({map[val], val});
    }

    void remove(long long val)
    {
        if (!map.count(val))
            return;

        remove({map[val], val});
        map[val]--;
        if (map[val] > 0) {
            insert({map[val], val});
        }
    }

    long long getSum() const { return sum; }

private:
    void insert(const std::pair<long long, long long>& p)
    {
        if (topX.size() == x && p < *topX.begin()) {
            remaining.insert(p);
            return;
        }
        sum += p.first * p.second;
        topX.insert(p);
        if (topX.size() > x) {
            sum -= topX.begin()->first * topX.begin()->second;
            remaining.insert(*topX.begin());
            topX.erase(topX.begin());
        }
    }

    void remove(const std::pair<long long, long long>& p)
    {
        if (p < *topX.begin()) {
            remaining.erase(p);
            return;
        }
        sum -= p.first * p.second;
        topX.erase(p);
        if (!remaining.empty()) {
            sum += remaining.rbegin()->first * remaining.rbegin()->second;
            topX.insert(*remaining.rbegin());
            remaining.erase(std::prev(remaining.end()));
        }
    }

private:
    std::unordered_map<long long, long long> map;        // <val, freq>
    std::set<std::pair<long long, long long>> topX;      // <freq, val>, ascending order
    std::set<std::pair<long long, long long>> remaining; // <freq, val>, ascending order
    long long sum{0};
    long long x;
};

class Solution
{
public:
    std::vector<long long> findXSum(std::vector<int>& nums, int k, int x)
    {
        const int n = nums.size();
        std::vector<long long> result;
        result.reserve(n - k + 1);
        Container container(x);
        for (int left = 0, right = 0; right < n; ++right) {
            container.insert(nums[right]);
            if (right >= k) {
                container.remove(nums[left]);
                left++;
            }
            if (right >= k - 1) {
                result.emplace_back(container.getSum());
            }
        }
        return result;
    }
};
