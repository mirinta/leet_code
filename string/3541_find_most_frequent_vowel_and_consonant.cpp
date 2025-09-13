#include <array>
#include <string>

/**
 * You are given a string s consisting of lowercase English letters ('a' to 'z').
 *
 * Your task is to:
 *
 * - Find the vowel (one of 'a', 'e', 'i', 'o', or 'u') with the maximum frequency.
 *
 * - Find the consonant (all other letters excluding vowels) with the maximum frequency.
 *
 * Return the sum of the two frequencies.
 *
 * Note: If multiple vowels or consonants have the same maximum frequency, you may choose any one of
 * them. If there are no vowels or no consonants in the string, consider their frequency as 0.
 *
 * The frequency of a letter x is the number of times it occurs in the string.
 *
 * ! 1 <= s.length <= 100
 * ! s consists of lowercase English letters only.
 */

class Solution
{
public:
    int maxFreqSum(std::string s)
    {
        std::array<int, 26> count{};
        int maxVowelFreq = 0;
        int maxConsonantFreq = 0;
        for (const auto& c : s) {
            count[c - 'a']++;
            if (isVowel(c)) {
                maxVowelFreq = std::max(maxVowelFreq, count[c - 'a']);
            } else {
                maxConsonantFreq = std::max(maxConsonantFreq, count[c - 'a']);
            }
        }
        return maxVowelFreq + maxConsonantFreq;
    }

private:
    bool isVowel(char c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }
};