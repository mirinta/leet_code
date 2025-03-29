#include <algorithm>
#include <stack>
#include <vector>

/**
 * You are given an array nums of n positive integers and an integer k.
 *
 * Initially, you start with a score of 1. You have to maximize your score by applying the following
 * operation at most k times:
 *
 * - Choose any non-empty subarray nums[l, ..., r] that you haven't chosen previously.
 *
 * - Choose an element x of nums[l, ..., r] with the highest prime score. If multiple such elements
 * exist, choose the one with the smallest index.
 *
 * - Multiply your score by x.
 *
 * Here, nums[l, ..., r] denotes the subarray of nums starting at index l and ending at the index r,
 * both ends being inclusive.
 *
 * The prime score of an integer x is equal to the number of distinct prime factors of x. For
 * example, the prime score of 300 is 3 since 300 = 2 * 2 * 3 * 5 * 5.
 *
 * Return the maximum possible score after applying at most k operations.
 *
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * ! 1 <= nums.length == n <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= k <= min(n * (n + 1) / 2, 10^9)
 */

class Solution
{
public:
    int maximumScore(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        const auto scores = getScores(nums);
        const auto prevGreaterEqual = getPrevGreaterEqual(scores);
        const auto nextGreater = getNextGreater(scores);
        std::vector<std::pair<int, long long>> data(
            n); // <nums[i], num of subarrays that nums[i] has the highest prime score>
        for (int i = 0; i < n; ++i) {
            data[i] = {nums[i], 1LL * (i - prevGreaterEqual[i]) * (nextGreater[i] - i)};
        }
        std::sort(data.begin(), data.end(),
                  [](const auto& p1, const auto& p2) { return p1.first > p2.first; });
        long long result = 1;
        static constexpr long long kMod = 1e9 + 7;
        for (int i = 0; i < n && k > 0; ++i) {
            const long long count = std::min<long long>(k, data[i].second);
            result = result * fastPowMod(data[i].first, count, kMod) % kMod;
            k -= count;
        }
        return result;
    }

private:
    std::vector<int> getScores(const std::vector<int>& nums)
    {
        const int max = *std::max_element(nums.begin(), nums.end());
        std::vector<bool> isPrime(max + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;
        std::vector<int> count(max + 1, 0); // num of distinct prime factors
        for (int i = 2; i <= max; ++i) {
            if (!isPrime[i])
                continue;

            count[i] = 1;
            for (int j = 2 * i; j <= max; j += i) {
                isPrime[j] = false;
                count[j]++;
            }
        }
        std::vector<int> scores(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            scores[i] = count[nums[i]];
        }
        return scores;
    }

    std::vector<int> getPrevGreaterEqual(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] > nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<int> getNextGreater(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] >= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }

    long long fastPowMod(long long a, long long b, long long mod)
    {
        long long result = 1;
        long long base = a;
        while (b > 0) {
            if (b & 1) {
                result = result * base % mod;
            }
            base = base * base % mod;
            b >>= 1;
        }
        return result;
    }
};