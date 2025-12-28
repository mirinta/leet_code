#include <string>

/**
 * For a string sequence, a string word is k-repeating if word concatenated k times is a substring
 * of sequence. The word's maximum k-repeating value is the highest value k where word is
 * k-repeating in sequence. If word is not a substring of sequence, word's maximum k-repeating value
 * is 0.
 *
 * Given strings sequence and word, return the maximum k-repeating value of word in sequence.
 *
 * ! 1 <= sequence.length <= 100
 * ! 1 <= word.length <= 100
 * ! sequence and word contains only lowercase English letters.
 */

class Solution {
public:
    int maxRepeating(std::string sequence, std::string word)
    {
        std::string s;
        int result = 0;
        while (s.size() < sequence.size()) {
            s.append(word);
            if (sequence.find(s) == std::string::npos)
                break;

            result++;
        }
        return result;
    }
};