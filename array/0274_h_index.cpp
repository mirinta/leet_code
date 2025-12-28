#include <vector>

/**
 * Given an array of integers citations where citations[i] is the number of citations a researcher
 * received for their ith paper, return the researcher's h-index.
 *
 * According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value
 * of h such that the given researcher has published at least h papers that have each been cited at
 * least h times.
 *
 * ! n == citations.length
 * ! 1 <= n <= 5000
 * ! 0 <= citations[i] <= 1000
 */

class Solution {
public:
    int hIndex(std::vector<int>& citations)
    {
        return approach1(citations);
    }

private:
    // time O(N), space O(N)
    int approach2(const std::vector<int>& citations)
    {
        const int n = citations.size();
        std::vector<int> map(1 + n, 0); // count[i]=j, num of papers of citation i = j
        for (const auto& val : citations) {
            map[std::min(n, val)]++;
        }
        int h = n;          // max value of h-index
        int count = map[h]; // num of papers with citation >= h
        while (h > count) {
            h--;
            count += map[h];
        }
        return h;
    }

    // time O(NlogN), space O(1)
    int approach1(const std::vector<int>& citations)
    {
        int lo = 1;
        int hi = citations.size();
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, citations)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

    bool isValid(int h, const std::vector<int>& citations)
    {
        int count = 0;
        for (const auto& val : citations) {
            if (val >= h) {
                count++;
            }
        }
        return count >= h;
    }
};