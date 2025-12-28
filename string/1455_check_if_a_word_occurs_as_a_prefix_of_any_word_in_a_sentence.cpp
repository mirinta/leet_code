#include <sstream>
#include <string>

/**
 * Given a sentence that consists of some words separated by a single space, and a searchWord, check
 * if searchWord is a prefix of any word in sentence.
 *
 * Return the index of the word in sentence (1-indexed) where searchWord is a prefix of this word.
 * If searchWord is a prefix of more than one word, return the index of the first word (minimum
 * index). If there is no such word return -1.
 *
 * A prefix of a string s is any leading contiguous substring of s.
 *
 * ! 1 <= sentence.length <= 100
 * ! 1 <= searchWord.length <= 10
 * ! sentence consists of lowercase English letters and spaces.
 * ! searchWord consists of lowercase English letters.
 */

class Solution {
public:
    int isPrefixOfWord(std::string sentence, std::string searchWord)
    {
        std::istringstream stream(sentence);
        std::string s;
        int i = 1;
        while (std::getline(stream, s, ' ')) {
            if (s.starts_with(searchWord))
                return i;

            i++;
        }
        return -1;
    }
};