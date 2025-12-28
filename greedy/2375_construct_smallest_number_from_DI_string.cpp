#include <functional>
#include <string>

/**
 * You are given a 0-indexed string pattern of length n consisting of the characters 'I' meaning
 * increasing and 'D' meaning decreasing.
 *
 * A 0-indexed string num of length n + 1 is created using the following conditions:
 *
 * - num consists of the digits '1' to '9', where each digit is used at most once.
 *
 * - If pattern[i] == 'I', then num[i] < num[i + 1].
 *
 * - If pattern[i] == 'D', then num[i] > num[i + 1].
 *
 * Return the lexicographically smallest possible string num that meets the conditions.
 *
 * ! 1 <= pattern.length <= 8
 * ! pattern consists of only the letters 'I' and 'D'.
 */

class Solution {
public:
    std::string smallestNumber(std::string pattern)
    {
        return approach2(pattern);
    }

private:
    std::string approach2(std::string& pattern)
    {
        pattern.insert(pattern.begin(), 'I');
        const int n = pattern.size();
        std::string result;
        int i = 0;
        int val = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && pattern[j] == 'D') {
                j++;
            }
            for (int k = j - i; k >= 1; --k) {
                result.push_back(k + val + '0');
            }
            val += j - i;
            i = j;
        }
        return result;
    }

    std::string approach1(std::string& pattern)
    {
        pattern.insert(pattern.begin(), 'I');
        std::string result(pattern.size(), 'x');
        std::string current{"0"};
        std::vector<bool> used(10, false);
        used[0] = true;
        std::function<void(int)> backtrack = [&](int i) {
            if (i == pattern.size()) {
                result = std::min(result, current.substr(1));
                return;
            }
            for (int j = 1; j <= 9; ++j) {
                if (used[j])
                    continue;

                if (pattern[i] == 'I' && j + '0' <= current.back())
                    continue;

                if (pattern[i] == 'D' && j + '0' >= current.back())
                    continue;

                used[j] = true;
                current.push_back(j + '0');
                backtrack(i + 1);
                used[j] = false;
                current.pop_back();
            }
        };
        backtrack(0);
        return result;
    }
};