#include <array>
#include <unordered_map>
#include <vector>

/**
 * You are given a string s consisting only of the characters 'a', 'b', and 'c'.
 *
 * A substring of s is called balanced if all distinct characters in the substring appear the same number of times.
 *
 * Return the length of the longest balanced substring of s.
 *
 * ! 1 <= s.length <= 10^5
 * ! s contains only the characters 'a', 'b', and 'c'.
 */

class Solution {
public:
    int longestBalanced(std::string& s)
    {
        int result = 0;
        result = std::max(result, case1('a', s));
        result = std::max(result, case1('b', s));
        result = std::max(result, case1('c', s));
        result = std::max(result, case2('a', 'b', s));
        result = std::max(result, case2('b', 'c', s));
        result = std::max(result, case2('a', 'c', s));
        result = std::max(result, case3(s));
        return result;
    }

private:
    int case1(char v, const std::string& s)
    {
        int count = 0;
        int result = 0;
        for (const auto& c : s) {
            if (c == v) {
                count++;
                result = std::max(result, count);
            } else {
                count = 0;
            }
        }
        return result;
    }

    int case2(char v1, char v2, const std::string& s)
    {
        // presum1[i] = num of v1 in s[0:i]
        // presum2[i] = num of v2 in s[0:i]
        // if s[j+1:i] is a valid subarray, then
        // presum1[i] - presum1[j] = presum2[i] - presum2[j]
        // presum1[i] - presum2[i] = presum1[j] - presum2[j]
        const int n = s.size();
        std::unordered_map<int, int> map{{0, -1}};
        int result = 0;
        for (int i = 0, count1 = 0, count2 = 0; i < n; ++i) {
            if (s[i] != v1 && s[i] != v2) {
                map = {{0, i}};
                count1 = 0;
                count2 = 0;
                continue;
            }
            count1 += s[i] == v1;
            count2 += s[i] == v2;
            const int target = count1 - count2;
            if (map.count(target)) {
                result = std::max(result, i - map[target]);
            } else {
                map[target] = i;
            }
        }
        return result;
    }

    int case3(const std::string& s)
    {
        const int n = s.size();
        std::array<int, 3> count{};
        std::unordered_map<long long, int> map;
        map[0] = -1;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            count[s[i] - 'a']++;
            const long long diff1 = count[0] - count[1];
            const long long diff2 = count[1] - count[2];
            const long long code = (diff1 << 32) + diff2;
            if (map.count(code)) {
                result = std::max(result, i - map[code]);
            } else {
                map[code] = i;
            }
        }
        return result;
    }
};