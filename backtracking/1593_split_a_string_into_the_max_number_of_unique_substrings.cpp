#include <string>
#include <unordered_set>

/**
 * Given a string s, return the maximum number of unique substrings that the given string can be
 * split into.
 *
 * You can split string s into any list of non-empty substrings, where the concatenation of the
 * substrings forms the original string. However, you must split the substrings such that all of
 * them are unique.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= s.length <= 16
 * ! s contains only lower case English letters.
 */

class Solution {
public:
    int maxUniqueSplit(std::string s)
    {
        std::unordered_set<std::string> set;
        int result = 0;
        backtrack(result, set, 0, 0, s);
        return result;
    }

private:
    void backtrack(int& result, std::unordered_set<std::string>& set, int start, int count, const std::string& s)
    {
        if (start == s.size()) {
            result = std::max(result, count);
            return;
        }
        if (count + s.size() - start <= result)
            return;

        for (int end = start; end < s.size(); ++end) {
            const auto sub = s.substr(start, end - start + 1);
            if (set.count(sub))
                continue;

            set.insert(sub);
            backtrack(result, set, end + 1, count + 1, s);
            set.erase(sub);
        }
    }
};