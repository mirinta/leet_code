#include <string>

/**
 * You are given a 0-indexed string word and an integer k.
 *
 * At every second, you must perform the following operations:
 *
 * - Remove the first k characters of word.
 *
 * - Add any k characters to the end of word.
 *
 * Note that you do not necessarily need to add the same characters that you removed. However, you
 * must perform both operations at every second.
 *
 * Return the minimum time greater than zero required for word to revert to its initial state.
 *
 * ! 1 <= word.length <= 50
 * ! 1 <= k <= word.length
 * ! word consists only of lowercase English letters.
 */

class Solution {
public:
    int minimumTimeToInitialState(std::string word, int k)
    {
        // let s be the processed word after each operation
        // during each operation:
        // - remove the first k characters of s
        // - add k #'s to the end of s, # can be any character
        //
        // after several times of operations, s may become:
        // si ... ... sn-1 # # ... #
        // |<-remaining->| |<-add->|, # can be any character
        //
        // if length of s[i:n-1] = L = 0, all characters are '#'s, return final answer
        // if s[i:n-1] == word[0:L-1], the following characters are '#'s, return final answer
        // otherwise, continue performing the operations
        const int n = word.size();
        int i = k; // we have to perform the operations once
        int remaining = n - k;
        int result = 1;
        while (remaining > 0 && word.substr(0, remaining) != word.substr(i, remaining)) {
            remaining -= k;
            i += k;
            result++;
        }
        return result;
    }
};