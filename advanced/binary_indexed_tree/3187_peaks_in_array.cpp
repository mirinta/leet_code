#include <vector>

/**
 * A peak in an array arr is an element that is greater than its previous and next element in arr.
 *
 * You are given an integer array nums and a 2D integer array queries.
 *
 * You have to process queries of two types:
 *
 * - queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
 *
 * - queries[i] = [2, indexi, vali], change nums[indexi] to vali.
 *
 * Return an array answer containing the results of the queries of the first type in order.
 *
 * Notes:
 *
 * - The first and the last element of an array or a subarray cannot be a peak.
 *
 * ! 3 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= queries.length <= 10^5
 * ! queries[i][0] == 1 or queries[i][0] == 2
 * ! For all i that:
 * ! queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
 * ! queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 10^5
 */

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(int n) : tree(n + 1, 0) {}

    void add(int i, long long delta)
    {
        if (!validate(i))
            return;

        while (i < tree.size()) {
            tree[i] += delta;
            i += lowbit(i);
        }
    }

    long long query(int left, int right)
    {
        if (left > right || !validate(left) || !validate(right))
            return 0;

        return presum(right) - presum(left - 1);
    }

private:
    int lowbit(int i)
    {
        return i & (-i);
    }

    bool validate(int i) const
    {
        return i >= 1 && i < tree.size();
    }

    long long presum(int i)
    {
        long long sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i);
        }
        return sum;
    }

private:
    std::vector<long long> tree;
};

class Solution {
public:
    std::vector<int> countOfPeaks(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        const int n = nums.size();
        BinaryIndexedTree tree(n);
        for (int i = 0; i < n; ++i) {
            if (isPeak(i, nums)) {
                tree.add(i + 1, 1);
            }
        }
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& query : queries) {
            if (query[0] == 1) {
                const auto& l = query[1];
                const auto& r = query[2];
                // nums[l] and nums[r] are not taken into account
                // thus, we need to query nums[l+1:r-1]
                result.push_back(tree.query(l + 2, r));
            } else {
                const auto& index = query[1];
                // changing nums[i] may change the status of nums[i-1], nums[i] and nums[i+1]
                for (int i = index - 1; i <= index + 1; ++i) {
                    if (isPeak(i, nums)) {
                        tree.add(i + 1, -1);
                    }
                }
                nums[index] = query[2];
                for (int i = index - 1; i <= index + 1; ++i) {
                    if (isPeak(i, nums)) {
                        tree.add(i + 1, 1);
                    }
                }
            }
        }
        return result;
    }

private:
    bool isPeak(int i, const std::vector<int>& nums)
    {
        if (i < 0 || i >= nums.size())
            return false;

        if (i - 1 < 0 || i + 1 >= nums.size())
            return false;

        return nums[i] > nums[i - 1] && nums[i] > nums[i + 1];
    }
};