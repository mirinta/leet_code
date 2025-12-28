#include <sstream>
#include <string>
#include <vector>

/**
 * You are given two strings sentence1 and sentence2, each representing a sentence composed of
 * words. A sentence is a list of words that are separated by a single space with no leading or
 * trailing spaces. Each word consists of only uppercase and lowercase English characters.
 *
 * Two sentences s1 and s2 are considered similar if it is possible to insert an arbitrary sentence
 * (possibly empty) inside one of these sentences such that the two sentences become equal. Note
 * that the inserted sentence must be separated from existing words by spaces.
 *
 * For example,
 *
 * - s1 = "Hello Jane" and s2 = "Hello my name is Jane" can be made equal by inserting "my name is"
 * between "Hello" and "Jane" in s1.
 *
 * - s1 = "Frog cool" and s2 = "Frogs are cool" are not similar, since although there is a sentence
 * "s are" inserted into s1, it is not separated from "Frog" by a space.
 *
 * Given two sentences sentence1 and sentence2, return true if sentence1 and sentence2 are similar.
 * Otherwise, return false.
 *
 * ! 1 <= sentence1.length, sentence2.length <= 100
 * ! sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
 * ! The words in sentence1 and sentence2 are separated by a single space.
 */

class Solution {
public:
    bool areSentencesSimilar(std::string sentence1, std::string sentence2)
    {
        if (sentence1.size() > sentence2.size())
            return areSentencesSimilar(sentence2, sentence1);

        const auto words1 = split(sentence1);
        const auto words2 = split(sentence2);
        int start = 0;
        int end1 = words1.size() - 1;
        int end2 = words2.size() - 1;
        while (start < words1.size() && words1[start] == words2[start]) {
            start++;
        }
        while (end1 >= 0 && words1[end1] == words2[end2]) {
            end1--;
            end2--;
        }
        return start > end1;
    }

private:
    std::vector<std::string> split(const std::string& str)
    {
        std::istringstream stream(str);
        std::string s;
        std::vector<std::string> result;
        while (std::getline(stream, s, ' ')) {
            result.push_back(s);
        }
        return result;
    }
};