#include <queue>
#include <vector>

/**
 * You are given a sorted integer array arr containing 1 and prime numbers, where all the integers
 * of arr are unique. You are also given an integer k.
 *
 * For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].
 *
 * Return the kth smallest fraction considered. Return your answer as an array of integers of size
 * 2, where answer[0] == arr[i] and answer[1] == arr[j].
 *
 * ! 2 <= arr.length <= 1000
 * ! 1 <= arr[i] <= 3 * 10^4
 * ! arr[0] == 1
 * ! arr[i] is a prime number for i > 0.
 * ! All the numbers of arr are unique and sorted in strictly increasing order.
 * ! 1 <= k <= arr.length * (arr.length - 1) / 2
 */

class Solution {
public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int>& arr, int k)
    {
        return approach2(arr, k);
    }

private:
    std::vector<int> approach2(const std::vector<int>& arr, int k)
    {
        const int n = arr.size();
        double lo = 0;
        double hi = 1.0;
        while (lo < hi) {
            const double mid = (hi + lo) / 2;
            double f = 0;
            int dividend = 0;
            int divisor = 0;
            int count = 0;
            for (int i = 0, j = 1; i < n - 1; ++i) {
                while (j < n && arr[i] * 1.0 / arr[j] > mid) {
                    j++;
                }
                count += n - j;
                if (j == n)
                    break;

                const double curr = arr[i] * 1.0 / arr[j];
                if (curr > f) {
                    dividend = arr[i];
                    divisor = arr[j];
                    f = curr;
                }
            }
            if (count == k)
                return {dividend, divisor};

            if (count > k) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        return {};
    }

    std::vector<int> approach1(const std::vector<int>& arr, int k)
    {
        const int n = arr.size();
        using Tuple = std::tuple<int, int, double>;
        auto compare = [](const auto& t1, const auto& t2) { return std::get<2>(t1) > std::get<2>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(compare)> pq(compare);
        for (int i = 1; i < n; ++i) {
            pq.emplace(0, i, arr[0] * 1.0 / arr[i]);
        }
        for (int t = 0; t < k - 1; ++t) {
            const auto [i, j, f] = pq.top();
            pq.pop();
            if (i + 1 < j) {
                pq.emplace(i + 1, j, arr[i + 1] * 1.0 / arr[j]);
            }
        }
        const auto [i, j, f] = pq.top();
        return {arr[i], arr[j]};
    }
};