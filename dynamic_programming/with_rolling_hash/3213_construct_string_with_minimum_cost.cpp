#include <map>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a string target, an array of strings words, and an integer array costs, both arrays
 * of the same length.
 *
 * Imagine an empty string s.
 *
 * You can perform the following operation any number of times (including zero):
 *
 * - Choose an index i in the range [0, words.length - 1].
 *
 * - Append words[i] to s.
 *
 * - The cost of operation is costs[i].
 *
 * Return the minimum cost to make s equal to target. If it's not possible, return -1.
 *
 * ! 1 <= target.length <= 5 * 10^4
 * ! 1 <= words.length == costs.length <= 5 * 10^4
 * ! 1 <= words[i].length <= target.length
 * ! The total sum of words[i].length is less than or equal to 5 * 10^4.
 * ! target and words[i] consist only of lowercase English letters.
 * ! 1 <= costs[i] <= 10^4
 */

class RangeHash {
    using LLONG = long long;

    static constexpr LLONG kMod = 1e9 + 7;
    static constexpr LLONG kBase = 26;

public:
    static LLONG valueOf(char c)
    {
        return c - 'a' + 1;
    }

    explicit RangeHash(const std::string& s) : prefixHash(s.size() + 1), powMod(s.size() + 1)
    {
        powMod[0] = 1;
        for (int i = 1; i <= s.size(); ++i) {
            prefixHash[i] = (prefixHash[i - 1] * kBase % kMod + valueOf(s[i - 1]) % kMod) % kMod;
            powMod[i] = powMod[i - 1] * kBase % kMod;
        }
    }

    // let L = right - left + 1
    // hash[left:right] = s[left] * Base^(L-1) + ... + s[right] * Base^0
    // where left and right are 0-indexed
    LLONG query(int left, int right) const
    {
        LLONG result = prefixHash[right + 1] - prefixHash[left] * powMod[right - left + 1] % kMod;
        result = (result + kMod) % kMod; // +kMod to prevent negative value
        return result;
    }

private:
    std::vector<LLONG> prefixHash; // prefixHash[i] = s[0] * Base^(i-1) + ... + s[i-1] * Base^0
    std::vector<LLONG> powMod;     // Base^i
};

class Solution {
public:
    int minimumCost(std::string target, std::vector<std::string>& words, std::vector<int>& costs)
    {
        // length, hash of words[i], cost of words[i]
        // where words[i].size() = length
        std::map<int, std::unordered_map<long long, int>> map;
        for (int i = 0; i < words.size(); ++i) {
            const int L = words[i].size();
            const auto hash = RangeHash(words[i]).query(0, L - 1);
            if (map.count(L) && map[L].count(hash)) {
                map[L][hash] = std::min(map[L][hash], costs[i]);
            } else {
                map[L][hash] = costs[i];
            }
        }
        // dp[i] = min cost to make s equal to target[0:i-1]
        // X X X X X X X X X X X X i
        // |<dp[i-L]>| |<---L--->|
        // |<-------dp[i]------->|
        RangeHash rangeHash(target);
        std::vector<int> dp(target.size() + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= target.size(); ++i) {
            for (const auto& [L, hashToCost] : map) {
                if (L > i)
                    break;

                if (dp[i - L] == INT_MAX)
                    continue;

                const auto hash = rangeHash.query(i - L, i - 1);
                if (!hashToCost.count(hash))
                    continue;

                dp[i] = std::min(dp[i], dp[i - L] + hashToCost.at(hash));
            }
        }
        return dp[target.size()] == INT_MAX ? -1 : dp[target.size()];
    }
};
