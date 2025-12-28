#include <algorithm>
#include <array>
#include <string>

/**
 * You are given a string word containing distinct lowercase English letters.
 *
 * Telephone keypads have keys mapped with distinct collections of lowercase English letters, which
 * can be used to form words by pushing them. For example, the key 2 is mapped with ["a","b","c"],
 * we need to push the key one time to type "a", two times to type "b", and three times to type "c".
 *
 * It is allowed to remap the keys numbered 2 to 9 to distinct collections of letters. The keys can
 * be remapped to any amount of letters, but each letter must be mapped to exactly one key. You need
 * to find the minimum number of times the keys will be pushed to type the string word.
 *
 * Return the minimum number of pushes needed to type word after remapping the keys.
 *
 * An example mapping of letters to keys on a telephone keypad is given below. Note that 1, *, #,
 * and 0 do not map to any letters.
 *
 * ! 1 <= word.length <= 10^5
 * ! word consists of lowercase English letters.
 */

class Solution {
public:
    int minimumPushes(std::string word)
    {
        // assign the top 1-8 frequent letters to numbers 2-9
        // assign the top 9~16 frequent letters to numbers 2-9
        // ...
        std::array<int, 26> freq{};
        for (const auto& c : word) {
            freq[c - 'a']++;
        }
        std::sort(freq.begin(), freq.end(), std::greater<>());
        int result = 0;
        for (int i = 0; i < 26; ++i) {
            result += freq[i] * (i / 8 + 1);
        }
        return result;
    }
};
