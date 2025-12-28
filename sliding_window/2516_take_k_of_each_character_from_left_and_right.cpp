#include <string>

/**
 * You are given a string s consisting of the characters 'a', 'b', and 'c' and a non-negative
 * integer k. Each minute, you may take either the leftmost character of s, or the rightmost
 * character of s.
 *
 * Return the minimum number of minutes needed for you to take at least k of each character, or
 * return -1 if it is not possible to take k of each character.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of only the letters 'a', 'b', and 'c'.
 * ! 0 <= k <= s.length
 */

class Solution {
public:
    int takeCharacters(std::string s, int k)
    {
        // 0 ... x-1 x ... y y+1 ... n-1
        // |<--A-->| |<-B->| |<---C--->|
        // we want:
        // countA[0:x-1] + countA[y+1:n-1] >= k
        // countB[0:x-1] + countB[y+1:n-1] >= k
        // countC[0:x-1] + countC[y+1:n-1] >= k
        // then:
        // countA[x:y] <= totalA - k
        // countB[x:y] <= totalB - k
        // countC[x:y] <= totalC - k
        // num of minutes = N - length of nums[x:y]
        // we need to maximize the length of nums[x:y]
        const int n = s.size();
        int totalA = 0;
        int totalB = 0;
        int totalC = 0;
        for (const auto& c : s) {
            totalA += c == 'a';
            totalB += c == 'b';
            totalC += c == 'c';
        }
        if (totalA < k || totalB < k || totalC < k)
            return -1;

        int countA = 0;
        int countB = 0;
        int countC = 0;
        int maxL = INT_MIN;
        for (int left = 0, right = 0; right < n; ++right) {
            countA += s[right] == 'a';
            countB += s[right] == 'b';
            countC += s[right] == 'c';
            while (countA > totalA - k || countB > totalB - k || countC > totalC - k) {
                countA -= s[left] == 'a';
                countB -= s[left] == 'b';
                countC -= s[left] == 'c';
                left++;
            }
            maxL = std::max(maxL, right - left + 1);
        }
        return maxL == INT_MIN ? -1 : n - maxL;
    }
};