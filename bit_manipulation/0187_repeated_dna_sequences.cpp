#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
 *
 * - For example, "ACGAATTCCG" is a DNA sequence.
 *
 * When studying DNA, it is useful to identify repeated sequences within the DNA.
 *
 * Given a string s that represents a DNA sequence, return all the 10-letter-long sequences
 * (substrings) that occur more than once in a DNA molecule. You may return the answer in any
 * order.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either 'A', 'C', 'G', or 'T'.
 */

class Solution {
public:
    std::vector<std::string> findRepeatedDnaSequences(std::string s)
    {
        return approach2(s);
    }

private:
    const std::unordered_map<char, int> value{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

    std::vector<std::string> approach2(const std::string& s)
    {
        if (s.size() <= 10)
            return {};

        const int n = s.size();
        std::unordered_map<int, int> map;
        std::unordered_set<int> visited;
        std::vector<std::string> result;
        for (int i = 0, mask = 0; i < n; ++i) {
            mask <<= 2;
            mask |= value.at(s[i]);
            if (i >= 10) {
                mask &= (1 << 20) - 1;
            }
            if (i >= 9 && ++map[mask] > 1 && !visited.count(mask)) {
                result.push_back(s.substr(i - 9, 10));
                visited.insert(mask);
            }
        }
        return result;
    }

    std::vector<std::string> approach1(const std::string& s)
    {
        if (s.size() <= 10)
            return {};

        constexpr int kMod = 1e9 + 7;
        const int n = s.size();
        std::unordered_map<int, int> map;
        std::unordered_set<int> visited;
        int powmod = 1;
        for (int i = 0; i < 9; ++i) {
            powmod = powmod * 4 % kMod;
        }
        std::vector<std::string> result;
        for (int i = 0, hash = 0; i < n; ++i) {
            if (i >= 10) {
                hash = (hash - powmod * value.at(s[i - 10]) % kMod + kMod) % kMod;
            }
            hash = (hash * 4 % kMod + value.at(s[i])) % kMod;
            if (i >= 9 && ++map[hash] > 1 && !visited.count(hash)) {
                result.push_back(s.substr(i - 9, 10));
                visited.insert(hash);
            }
        }
        return result;
    }
};