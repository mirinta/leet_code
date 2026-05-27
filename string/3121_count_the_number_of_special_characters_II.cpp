#include <array>
#include <string>

/**
 * You are given a string word. A letter c is called special if it appears both in lowercase and
 * uppercase in word, and every lowercase occurrence of c appears before the first uppercase
 * occurrence of c.
 *
 * Return the number of special letters in word.
 *
 * ! 1 <= word.length <= 2 * 10^5
 * ! word consists of only lowercase and uppercase English letters.
 */

class Solution {
public:
    int numberOfSpecialChars(std::string& word)
    {
        const int n = word.size();
        // <uppercase first index, lowercase last index>
        std::array<std::pair<int, int>, 26> info{};
        info.fill({INT_MAX, -1});
        for (int i = 0; i < n; ++i) {
            if (std::isupper(word[i])) {
                info[word[i] - 'A'].first = std::min(info[word[i] - 'A'].first, i);
            } else {
                info[word[i] - 'a'].second = i;
            }
        }
        int result = 0;
        for (const auto& [first, last] : info) {
            result += first != INT_MAX && last != -1 && first > last;
        }
        return result;
    }
};
