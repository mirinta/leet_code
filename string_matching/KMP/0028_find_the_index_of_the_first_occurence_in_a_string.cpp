#include <string>
#include <vector>

/**
 * Given two strings "needle" and "haystack", return the index of the first occurrence of "needle"
 * in "haystack", or "-1" if "needle" if not part of "haystack".
 *
 * ! 1 <= haystack.length, needle.length <= 10^4
 * ! haystack and needle consist of only lowercase English characters.
 */

class Solution {
public:
    int strStr(std::string haystack, std::string needle)
    {
        return approach2(haystack, needle);
    }

private:
    // KMP
    int approach2(const std::string& haystack, const std::string& needle)
    {
        if (needle.size() > haystack.size())
            return -1;

        const int n = haystack.size();
        const int m = needle.size();
        const auto next = preprocess(needle);
        int i = 0;
        int j = 0;
        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            } else if (j == 0) {
                i++;
            } else {
                j = next[j - 1];
            }
            if (j == m)
                return i - m;
        }
        return -1;
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

    // brute force
    int approach1(const std::string& haystack, const std::string& needle)
    {
        if (needle.size() > haystack.size())
            return -1;

        const int n = haystack.size();
        const int m = needle.size();
        for (int i = 0; i + m <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (needle[j] != haystack[j + i])
                    break;

                if (j == m - 1)
                    return i;
            }
        }
        return -1;
    }
};