#include <string>
#include <vector>

/**
 * You are given an integer num. You can swap two digits at most once to get the maximum valued
 * number.
 *
 * Return the maximum valued number you can get.
 *
 * ! 0 <= num <= 10^8
 */

class Solution {
public:
    int maximumSwap(int num)
    {
        auto s = std::to_string(num);
        const int n = s.size();
        // suffixMax[i] = index of the max element of s[i:n-1]
        std::vector<int> suffixMax(n);
        suffixMax[n - 1] = n - 1;
        for (int i = n - 2; i >= 0; --i) {
            if (s[i] > s[suffixMax[i + 1]]) {
                suffixMax[i] = i;
            } else {
                suffixMax[i] = suffixMax[i + 1];
            }
        }
        for (int i = 0; i < n; ++i) {
            if (s[i] < s[suffixMax[i]]) {
                std::swap(s[i], s[suffixMax[i]]);
                return std::stoi(s);
            }
        }
        return num;
    }
};
