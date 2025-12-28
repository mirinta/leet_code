#include <array>
#include <string>
#include <vector>

/**
 * Given a list of words, list of  single letters (might be repeating) and score of every character.
 *
 * Return the maximum score of any valid set of words formed by using the given letters (words[i]
 * cannot be used two or more times).
 *
 * It is not necessary to use all characters in letters and each letter can only be used once. Score
 * of letters 'a', 'b', 'c', ... ,'z' is given by score[0], score[1], ... , score[25] respectively.
 *
 * ! 1 <= words.length <= 14
 * ! 1 <= words[i].length <= 15
 * ! 1 <= letters.length <= 100
 * ! letters[i].length == 1
 * ! score.length == 26
 * ! 0 <= score[i] <= 10
 * ! words[i], letters[i] contains only lower case English letters.
 */

class Solution {
public:
    int maxScoreWords(std::vector<std::string>& words, std::vector<char>& letters, std::vector<int>& score)
    {
        std::array<int, 26> total{};
        for (const auto& c : letters) {
            total[c - 'a']++;
        }
        std::vector<std::array<int, 26>> candidates;
        for (const auto& s : words) {
            bool isValid = true;
            std::array<int, 26> count{};
            for (const auto& c : s) {
                if (total[c - 'a'] == 0) {
                    isValid = false;
                    break;
                }
                count[c - 'a']++;
            }
            if (isValid) {
                candidates.push_back(std::move(count));
            }
        }
        const int n = candidates.size();
        int result = 0;
        for (int i = 1; i < (1 << n); ++i) {
            result = std::max(result, helper(i, n, total, candidates, score));
        }
        return result;
    }

private:
    int helper(int mask,
               int n,
               const std::array<int, 26>& total,
               const std::vector<std::array<int, 26>>& candidates,
               const std::vector<int>& score)
    {
        std::array<int, 26> count{};
        for (int i = 0; i < n; ++i) {
            if (!(mask >> i & 1))
                continue;

            for (int j = 0; j < 26; ++j) {
                count[j] += candidates[i][j];
                if (count[j] > total[j])
                    return 0;
            }
        }
        int result = 0;
        for (int j = 0; j < 26; ++j) {
            result += count[j] * score[j];
        }
        return result;
    }
};