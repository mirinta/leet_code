#include <queue>
#include <vector>

/**
 * An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
 *
 * Given an integer n, return the nth ugly number.
 *
 * ! 1 <= n <= 1690
 */

class Solution {
public:
    int nthUglyNumber(int n)
    {
        return approach2(n);
    }

private:
    int approach2(int n)
    {
        // three pointers:
        std::vector<int> result{1};
        for (int i = 0, j = 0, k = 0, t = 0; t < n - 1; ++t) {
            const int num1 = result[i] * 2;
            const int num2 = result[j] * 3;
            const int num3 = result[k] * 5;
            result.push_back(std::min({num1, num2, num3}));
            if (result.back() == num1) {
                i++;
            }
            if (result.back() == num2) {
                j++;
            }
            if (result.back() == num3) {
                k++;
            }
        }
        return result.back();
    }

    int approach1(int n)
    {
        // if x is an ugly number,
        // then 2x, 3x, and 5x are all ugly numbers
        // - x = 1, the next ugly numbers are 2, 3, and 5
        // - x = 2, the next ugly numbers are 4, 6, and 10
        std::priority_queue<long long, std::vector<long long>, std::greater<>> pq;
        pq.push(1);
        int count = 0;
        while (!pq.empty()) {
            const auto top = pq.top();
            pq.pop();
            if (count == n - 1)
                return top;

            // skip duplicates
            while (!pq.empty() && top == pq.top()) {
                pq.pop();
            }
            count++;
            pq.push(2 * top);
            pq.push(3 * top);
            pq.push(5 * top);
        }
        return -1;
    }
};
