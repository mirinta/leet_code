#include <array>
#include <climits>
#include <vector>

/**
 * There are n soldiers standing in a line. Each soldier is assigned a unique rating value.
 *
 * You have to form a team of 3 soldiers amongst them under the following rules:
 *
 * - Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
 *
 * - A team is valid if: (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k])
 * where (0 <= i < j < k < n).
 *
 * Return the number of teams you can form given the conditions. (soldiers can be part of multiple
 * teams).
 *
 * ! n == rating.length
 * ! 3 <= n <= 1000
 * ! 1 <= rating[i] <= 10^5
 * ! All the integers in rating are unique.
 */

class BinaryIndexedTree {
    using LLONG = long long;

public:
    explicit BinaryIndexedTree(LLONG n) : tree(n + 1) {}

    void add(LLONG i, LLONG delta)
    {
        for (; i < tree.size(); i += lowbit(i)) {
            tree[i] += delta;
        }
    }

    void reset()
    {
        std::fill(tree.begin(), tree.end(), 0);
    }

    LLONG query(LLONG left, LLONG right)
    {
        return presum(right) - presum(left - 1);
    }

private:
    LLONG lowbit(LLONG i)
    {
        return i & (-i);
    }

    LLONG presum(LLONG i)
    {
        LLONG sum = 0;
        for (; i > 0; i -= lowbit(i)) {
            sum += tree[i];
        }
        return sum;
    }

private:
    std::vector<LLONG> tree;
};

class Solution {
public:
    int numTeams(std::vector<int>& rating)
    {
        return approach2(rating);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& val : nums) {
            min = std::min(min, val);
            max = std::max(max, val);
        }
        BinaryIndexedTree leftBIT(max);
        BinaryIndexedTree rightBIT(max);
        for (const auto& val : nums) {
            rightBIT.add(val, 1);
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int countSmallerLeft = i - leftBIT.query(nums[i], max);
            const int countGreaterLeft = i - leftBIT.query(min, nums[i]);
            leftBIT.add(nums[i], 1);
            rightBIT.add(nums[i], -1);
            const int countSmallerRight = n - i - 1 - rightBIT.query(nums[i], max);
            const int countGreaterRight = n - i - 1 - rightBIT.query(min, nums[i]);
            result += countSmallerLeft * countGreaterRight;
            result += countGreaterLeft * countSmallerRight;
        }
        return result;
    }

    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // left[i][0] = num of elements of nums[0:i) which are < nums[i]
        // left[i][1] = num of elements of nums[0:i) which are > nums[i]
        std::vector<std::array<int, 2>> left(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                left[i][0] += nums[i] > nums[j];
                left[i][1] += nums[i] < nums[j];
            }
        }
        // right[i][0] = num of elements of nums(i:n) which are < nums[i]
        // right[i][1] = num of elements of nums(i:n) which are > nums[i]
        std::vector<std::array<int, 2>> right(n);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j > i; --j) {
                right[i][0] += nums[i] > nums[j];
                right[i][1] += nums[i] < nums[j];
            }
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += left[i][0] * right[i][1];
            result += left[i][1] * right[i][0];
        }
        return result;
    }
};
