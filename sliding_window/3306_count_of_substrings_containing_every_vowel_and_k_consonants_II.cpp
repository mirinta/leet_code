#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a string word and a non-negative integer k.
 *
 * Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and
 * 'u') at least once and exactly k consonants.
 *
 * ! 5 <= word.length <= 2 * 10^5
 * ! word consists only of lowercase English letters.
 * ! 0 <= k <= word.length - 5
 */

class Solution {
public:
    long long countOfSubstrings(std::string word, int k)
    {
        const int n = word.size();
        // count[i] = num of consecutive vowels to the right of word[i]
        std::vector<long long> count(n, 0);
        for (int i = n - 2; i >= 0; --i) {
            if (isVowel(word[i + 1])) {
                count[i] = 1 + count[i + 1];
            }
        }
        std::unordered_map<char, long long> map; // for vowels
        long long consonants = 0;
        long long result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            if (isVowel(word[right])) {
                map[word[right]]++;
            } else {
                consonants++;
            }
            while (map.size() == 5 && consonants >= k) {
                if (consonants == k) {
                    result += 1 + count[right];
                }
                if (isVowel(word[left])) {
                    if (--map[word[left]] == 0) {
                        map.erase(word[left]);
                    }
                } else {
                    consonants--;
                }
                left++;
            }
        }
        return result;
    }

private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
