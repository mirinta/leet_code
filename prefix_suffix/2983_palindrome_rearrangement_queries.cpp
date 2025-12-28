#include <array>
#include <string>
#include <vector>

/**
 * You are given a 0-indexed string s having an even length n.
 *
 * You are also given a 0-indexed 2D integer array, queries, where queries[i] = [ai, bi, ci, di].
 *
 * For each query i, you are allowed to perform the following operations:
 *
 * - Rearrange the characters within the substring s[ai:bi], where 0 <= ai <= bi < n / 2.
 *
 * - Rearrange the characters within the substring s[ci:di], where n / 2 <= ci <= di < n.
 *
 * For each query, your task is to determine whether it is possible to make s a palindrome by
 * performing the operations.
 *
 * Each query is answered independently of the others.
 *
 * Return a 0-indexed array answer, where answer[i] == true if it is possible to make s a palindrome
 * by performing operations specified by the ith query, and false otherwise.
 *
 * A substring is a contiguous sequence of characters within a string.
 * s[x:y] represents the substring consisting of characters from the index x to index y in s, both
 * inclusive.
 *
 * ! 2 <= n == s.length <= 10^5
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length == 4
 * ! ai == queries[i][0], bi == queries[i][1]
 * ! ci == queries[i][2], di == queries[i][3]
 * ! 0 <= ai <= bi < n / 2
 * ! n / 2 <= ci <= di < n
 * ! n is even.
 * ! s consists of only lowercase English letters.
 */

class Solution {
public:
    std::vector<bool> canMakePalindromeQueries(std::string s, std::vector<std::vector<int>>& queries)
    {
        n = s.size() / 2;
        const auto s1 = std::string(s.begin(), s.begin() + n);
        const auto s2 = std::string(s.rbegin(), s.rbegin() + n);
        std::vector<std::array<int, 26>> presum1(n + 1);
        std::vector<std::array<int, 26>> presum2(n + 1);
        diff.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            presum1[i] = presum1[i - 1];
            presum2[i] = presum2[i - 1];
            const auto& c1 = s1[i - 1];
            const auto& c2 = s2[i - 1];
            presum1[i][c1 - 'a']++;
            presum2[i][c2 - 'a']++;
            diff[i] = diff[i - 1] + (c1 == c2 ? 0 : 1);
        }
        std::vector<bool> result(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            const int l1 = queries[i][0];
            const int r1 = queries[i][1];
            const int l2 = s.size() - 1 - queries[i][3];
            const int r2 = s.size() - 1 - queries[i][2];
            result[i] = check(presum1, l1, r1, presum2, l2, r2);
        }
        return result;
    }

private:
    int n{0};              // half length of s = s1.length = s2.length
    std::vector<int> diff; // diff[i] = num of different characters between s1[0:i) and s2[0:i)

    bool check(const std::vector<std::array<int, 26>>& presum1,
               int l1,
               int r1,
               const std::vector<std::array<int, 26>>& presum2,
               int l2,
               int r2)
    {
        if (l1 > l2)
            return check(presum2, l2, r2, presum1, l1, r1);

        if (!isSame(0, l1 - 1) || !isSame(std::max(r1, r2) + 1, n - 1))
            return false;

        // case 1:
        // |<---------l2-------------r2------->|
        // |<---l1-----------------------r1--->|
        if (r1 >= r2)
            return count(presum1, l1, r1) == count(presum2, l1, r1);

        // case 2:
        // |<-----------------l2-----r2------->|
        // |<---l1-------r1------------------->|
        if (r1 < l2)
            return isSame(r1 + 1, l2 - 1) && count(presum1, l1, r1) == count(presum2, l1, r1) &&
                   count(presum1, l2, r2) == count(presum2, l2, r2);

        // case 3:
        // |<------------ l2---------r2------->|
        // |<--------l1---------r1------------>|
        auto count1 = count(presum1, l1, r1);
        if (!subtract(count1, count(presum2, l1, l2 - 1)))
            return false;

        auto count2 = count(presum2, l2, r2);
        if (!subtract(count2, count(presum1, r1 + 1, r2)))
            return false;

        return count1 == count2;
    }

    std::array<int, 26> count(const std::vector<std::array<int, 26>>& presum, int lo, int hi)
    {
        std::array<int, 26> result;
        for (int i = 0; i < 26; ++i) {
            result[i] = presum[hi + 1][i] - presum[lo][i];
        }
        return result;
    }

    bool subtract(std::array<int, 26>& count1, const std::array<int, 26>& count2)
    {
        for (int i = 0; i < 26; ++i) {
            count1[i] -= count2[i];
            if (count1[i] < 0)
                return false;
        }
        return true;
    }

    bool isSame(int lo, int hi)
    {
        return diff[hi + 1] - diff[lo] == 0;
    }
};