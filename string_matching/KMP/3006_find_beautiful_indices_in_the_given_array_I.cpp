#include <algorithm>
#include <string>
#include <vector>

/**
 * You are given a 0-indexed string s, a string a, a string b, and an integer k.
 *
 * An index i is beautiful if:
 *
 * - 0 <= i <= s.length - a.length
 *
 * - s[i..(i + a.length - 1)] == a
 *
 * - There exists an index j such that:
 *
 *     - 0 <= j <= s.length - b.length
 *
 *     - s[j..(j + b.length - 1)] == b
 *
 *     - |j - i| <= k
 *
 * Return the array that contains beautiful indices in sorted order from smallest to largest.
 *
 * ! 1 <= k <= s.length <= 10^5
 * ! 1 <= a.length, b.length <= 10
 * ! s, a, and b contain only lowercase English letters.
 */

class Solution {
public:
    std::vector<int> beautifulIndices(std::string s, std::string a, std::string b, int k)
    {
        const auto I = kmp(s, a);
        const auto J = kmp(s, b);
        std::vector<int> result;
        for (const auto& i : I) {
            auto upper = std::upper_bound(J.begin(), J.end(), i + k); // j > i+k
            auto lower = std::lower_bound(J.begin(), J.end(), i - k); // j >= i-k
            // we want i-k <= j <= i+k
            if (lower != J.end() && lower < upper) {
                result.push_back(i);
            }
        }
        return result;
    }

private:
    std::vector<int> kmp(const std::string& s, const std::string& p)
    {
        const int n = s.size();
        const auto next = preprocess(p);
        int i = 0;
        int j = 0;
        std::vector<int> result;
        while (i < n) {
            if (s[i] == p[j]) {
                i++;
                j++;
            } else if (j > 0) {
                j = next[j - 1];
            } else {
                i++;
            }
            if (j == p.size()) {
                result.push_back(i - p.size());
                j = next[p.size() - 1];
            }
        }
        return result;
    }

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