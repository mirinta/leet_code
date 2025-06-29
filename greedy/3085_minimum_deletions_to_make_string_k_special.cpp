#include <array>
#include <string>

/**
 * You are given a string word and an integer k.
 *
 * We consider word to be k-special if |freq(word[i]) - freq(word[j])| <= k for all indices i and j
 * in the string.
 *
 * Here, freq(x) denotes the frequency of the character x in word, and |y| denotes the absolute
 * value of y.
 *
 * Return the minimum number of characters you need to delete to make word k-special.
 *
 * ! 1 <= word.length <= 10^5
 * ! 0 <= k <= 10^5
 * ! word consists only of lowercase English letters.
 */

class Solution
{
public:
    int minimumDeletions(std::string word, int k)
    {
        std::array<int, 26> count{};
        for (const auto& c : word) {
            count[c - 'a']++;
        }
        int result = word.size();
        // choose count[i] as the minimum frequency
        // for every j != i:
        // if count[j] < count[i], remove all count[j]
        // if count[j] - count[i] > k, let count[j] -= count[j] - count[i] - k
        for (int i = 0; i < 26; ++i) {
            if (count[i] == 0)
                continue;

            int remove = 0;
            for (int j = 0; j < 26; ++j) {
                if (i == j || count[j] == 0)
                    continue;

                if (count[j] < count[i]) {
                    remove += count[j];
                } else if (count[j] - count[i] > k) {
                    remove += count[j] - count[i] - k;
                }
            }
            result = std::min(result, remove);
        }
        return result;
    }
};
