#include <string>
#include <vector>

/**
 * A string s can be partitioned into groups of size k using the following procedure:
 *
 * - The first group consists of the first k characters of the string, the second group consists of
 * the next k characters of the string, and so on. Each element can be a part of exactly one group.
 *
 * - For the last group, if the string does not have k characters remaining, a character fill is
 * used to complete the group.
 *
 * Note that the partition is done so that after removing the fill character from the last group (if
 * it exists) and concatenating all the groups in order, the resultant string should be s.
 *
 * Given the string s, the size of each group k and the character fill, return a string array
 * denoting the composition of every group s has been divided into, using the above procedure.
 *
 * ! 1 <= s.length <= 100
 * ! s consists of lowercase English letters only.
 * ! 1 <= k <= 100
 * ! fill is a lowercase English letter.
 */

class Solution {
public:
    std::vector<std::string> divideString(std::string s, int k, char fill)
    {
        std::vector<std::string> result;
        for (int i = 0; i < s.size(); i += k) {
            std::string sub;
            sub.reserve(k);
            sub.assign(s, i, k);
            if (sub.size() < k) {
                sub.insert(sub.end(), k - sub.size(), fill);
            }
            result.push_back(std::move(sub));
        }
        return result;
    }
};