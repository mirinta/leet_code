#include <cmath>
#include <string>
#include <vector>

/**
 * You are given a 0-indexed string word and an integer k.
 *
 * At every second, you must perform the following operations:
 *
 * - Remove the first k characters of word.
 *
 * - Add any k characters to the end of word.
 *
 * Note that you do not necessarily need to add the same characters that you removed. However, you
 * must perform both operations at every second.
 *
 * Return the minimum time greater than zero required for word to revert to its initial state.
 *
 * ! 1 <= word.length <= 10^6
 * ! 1 <= k <= word.length
 * ! word consists only of lowercase English letters.
 */

class Solution {
public:
    int minimumTimeToInitialState(std::string word, int k)
    {
        // 0 ... X n-L-1 n-L ... n-1
        // |<---n-L--->| |<---L--->|
        // L is the length of longest equal proper prefix and proper suffix of s[0:n-1]
        // if (n-L) % k = 0, then we can apply (n-L)/k operations till s[n-L] is the front
        // otherwise, let L = length of the second longest ... of s[0:n-1]
        const int n = word.size();
        const auto next = preprocess(word);
        int length = next[n - 1];
        while (length > 0 && (n - length) % k != 0) {
            length = next[length - 1];
        }
        if (length == 0)
            return std::ceil(1.0 * n / k);

        return (n - length) / k;
    }

private:
    std::vector<int> preprocess(const std::string& s)
    {
        const int n = s.size();
        std::vector<int> next(n, 0);
        next[0] = 0;
        for (int i = 1; i < n; ++i) {
            int L = next[i - 1];
            while (L >= 1 && s[i] != s[L]) {
                L = next[L - 1];
            }
            next[i] = L + (s[i] == s[L]);
        }
        return next;
    }
};