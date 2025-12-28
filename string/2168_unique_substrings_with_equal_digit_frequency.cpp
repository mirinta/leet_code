#include <array>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given a digit string s, return the number of unique substrings of s where every digit appears the
 * same number of times.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of digits.
 */

class RangeHash {
public:
    explicit RangeHash(const std::string& s) : prefixHash(s.size() + 1), powMod(s.size() + 1)
    {
        powMod[0] = 1;
        for (int i = 1; i <= s.size(); ++i) {
            powMod[i] = powMod[i - 1] * kBase % kMod;
            prefixHash[i] = (prefixHash[i - 1] * kBase % kMod + valueOf(s[i - 1]) % kMod) % kMod;
        }
    }

    long long query(int left, int right)
    {
        long long result = prefixHash[right + 1] - prefixHash[left] * powMod[right - left + 1] % kMod;
        result = (result + kMod) % kMod;
        return result;
    }

private:
    long long valueOf(char c)
    {
        return c - '0' + 1;
    }

private:
    static constexpr long long kMod = 1e9 + 7;
    static constexpr long long kBase = 11;

    std::vector<long long> prefixHash;
    std::vector<long long> powMod;
};

class Solution {
public:
    int equalDigitFrequency(std::string s)
    {
        const int n = s.size();
        std::vector<std::array<int, 10>> count(n + 1);
        for (int i = 1; i <= n; ++i) {
            count[i] = count[i - 1];
            count[i][s[i - 1] - '0']++;
        }
        auto isValid = [&](int left, int right) {
            int target = -1;
            for (int i = 0; i < 10; ++i) {
                const int freq = count[right + 1][i] - count[left][i];
                if (freq == 0)
                    continue;

                if (target != -1 && target != freq)
                    return false;

                if (target == -1) {
                    target = freq;
                }
            }
            return true;
        };
        RangeHash rangeHash(s);
        std::unordered_set<long long> set;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                const long long hash = rangeHash.query(i, j);
                if (isValid(i, j)) {
                    set.insert(hash);
                }
            }
        }
        return set.size();
    }
};