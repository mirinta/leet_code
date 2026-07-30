#include <algorithm>
#include <string>
#include <vector>

/**
 * Given an array of keywords words and a string s, make all appearances of all keywords words[i] in
 * s bold. Any letters between <b> and </b> tags become bold.
 *
 * Return s after adding the bold tags. The returned string should use the least number of tags
 * possible, and the tags should form a valid combination.
 *
 * ! 1 <= s.length <= 500
 * ! 0 <= words.length <= 50
 * ! 1 <= words[i].length <= 10
 * ! s and words[i] consist of lowercase English letters.
 *
 * ! This question is the same as LC.616.
 */

class Solution {
public:
    std::string boldWords(std::vector<std::string>& words, std::string& s)
    {
        const int n = s.size();
        std::vector<bool> mask(n, false);
        for (const auto& word : words) {
            int start = s.find(word);
            while (start != std::string::npos) {
                std::fill(mask.begin() + start, mask.begin() + start + word.size(), true);
                start = s.find(word, start + 1);
            }
        }
        std::string result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (mask[i] && (i == 0 || !mask[i - 1])) {
                result.append("<b>");
            }
            result.push_back(s[i]);
            if (mask[i] && (i == n - 1 || !mask[i + 1])) {
                result.append("</b>");
            }
        }
        return result;
    }
};