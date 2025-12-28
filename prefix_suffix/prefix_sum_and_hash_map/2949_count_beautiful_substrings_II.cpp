#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a string s and a positive integer k.
 *
 * Let vowels and consonants be the number of vowels and consonants in a string.
 *
 * A string is beautiful if:
 *
 * - vowels == consonants.
 *
 * - (vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is
 * divisible by k. Return the number of non-empty beautiful substrings in the given string s.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 * Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
 *
 * Consonant letters in English are every letter except vowels.
 *
 * ! 1 <= s.length <= 5 * 10^4
 * ! 1 <= k <= 1000
 * ! s consists of only English lowercase letters.
 */

class Solution {
public:
    long long beautifulSubstrings(std::string s, int k)
    {
        // let vowel letters = 1 and consonant letters = -1
        // if vowels = consonants, then sum of s[j:i] = 0
        // let L = length of s[j:i]
        // if (vowels*consonants) % k = (L^2/4) % k = 0, then L^2 % 4k = 0
        // we can find minL such that (minL^2) % 4k = 0
        //
        // given sum[i], if we can find sum[j] = sum[i]
        // then s[j+1:i] is a valid substring with length L = i-j
        // L must be divisible by minL, then (i-j) % minL = 0
        // thus, i % minL = j % minL
        const int n = s.size();
        int minL = 1;
        while (minL * minL % (4 * k) != 0) {
            minL++;
        }
        // map[sum[i]][i%minL] = num of j such that sum[i]=sum[j] and i % minL = j % minL
        // base case:
        // sum[i] = 0, then s[0:i] is a valid substring, L = i+1
        // we want (i+1) % minL = 0, then (i % minL + 1) % minL = 0
        // thus, i % minL = minL - 1, i.e., map[0][minL-1] = 1
        std::unordered_map<int, std::unordered_map<int, int>> map;
        map[0][minL - 1] = 1;
        int sum = 0;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            sum += isVowel(s[i]) ? 1 : -1;
            if (map.count(sum) && map[sum].count(i % minL)) {
                result += map[sum][i % minL];
            }
            map[sum][i % minL]++;
        }
        return result;
    }

private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};