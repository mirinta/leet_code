#include <cmath>
#include <string>
#include <vector>

/**
 * Given an array of strings words and a width maxWidth, format the text such that each line has
 * exactly maxWidth characters and is fully (left and right) justified.
 *
 * You should pack your words in a greedy approach; that is, pack as many words as you can in each
 * line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
 *
 * Extra spaces between words should be distributed as evenly as possible. If the number of spaces
 * on a line does not divide evenly between words, the empty slots on the left will be assigned more
 * spaces than the slots on the right.
 *
 * For the last line of text, it should be left-justified, and no extra space is inserted between
 * words.
 *
 * Note:
 *
 * - A word is defined as a character sequence consisting of non-space characters only.
 *
 * - Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
 *
 * - The input array words contains at least one word.
 *
 * ! 1 <= words.length <= 300
 * ! 1 <= words[i].length <= 20
 * ! words[i] consists of only English letters and symbols.
 * ! 1 <= maxWidth <= 100
 * ! words[i].length <= maxWidth
 */

class Solution {
public:
    std::vector<std::string> fullJustify(std::vector<std::string>& words, int maxWidth)
    {
        std::vector<std::string> result;
        int left = 0;
        int right = 0;
        int length = 0;
        while (right < words.size()) {
            length += words[right].size();
            // at least one space between each word
            if (length + std::max(0, right - left) > maxWidth) {
                result.push_back(generateFullyJustified(left, right - 1, maxWidth, words));
                left = right;
                length = 0;
            } else {
                right++;
            }
        }
        if (right - left >= 1) {
            result.push_back(generateLeftJustified(left, right - 1, maxWidth, words));
        }
        return result;
    }

    std::string generateFullyJustified(int left, int right, int maxWidth, const std::vector<std::string>& words)
    {
        // words[left:right]
        if (right - left + 1 <= 0)
            return {};

        std::string result;
        int spaces = maxWidth;
        for (int i = left; i <= right; ++i) {
            spaces -= words[i].size();
        }
        for (int i = left; i <= right; ++i) {
            result.append(words[i]);
            if (spaces > 0) {
                std::string temp(right - i > 0 ? std::ceil(1.0 * spaces / (right - i)) : spaces, ' ');
                spaces -= temp.size();
                result.append(temp);
            }
        }
        return result;
    }

    std::string generateLeftJustified(int left, int right, int maxWidth, const std::vector<std::string>& words)
    {
        // words[left, right]
        if (right - left + 1 <= 0)
            return {};

        std::string result;
        for (int i = left; i <= right; ++i) {
            result.append(words[i]);
            if (i < right) {
                result.push_back(' ');
            }
        }
        for (int i = result.size(); i < maxWidth; ++i) {
            result.push_back(' ');
        }
        return result;
    }
};
