#include <string>
#include <vector>

/**
 * Given an array of strings words, return the first palindromic string in the array. If there is no
 * such string, return an empty string "".
 *
 * A string is palindromic if it reads the same forward and backward.
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 100
 * ! words[i] consists only of lowercase English letters.
 */

class Solution {
public:
    std::string firstPalindrome(std::vector<std::string>& words)
    {
        for (const auto& word : words) {
            if (isPalindrome(word))
                return word;
        }
        return {};
    }

private:
    bool isPalindrome(const std::string& word)
    {
        int lo = 0;
        int hi = word.size() - 1;
        while (lo < hi) {
            if (word[lo] != word[hi])
                return false;

            lo++;
            hi--;
        }
        return true;
    }
};