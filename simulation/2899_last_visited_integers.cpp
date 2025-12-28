#include <string>
#include <vector>

/**
 * Given a 0-indexed array of strings words where words[i] is either a positive integer represented
 * as a string or the string "prev".
 *
 * Start iterating from the beginning of the array; for every "prev" string seen in words, find the
 * last visited integer in words which is defined as follows:
 *
 * - Let k be the number of consecutive "prev" strings seen so far (containing the current string).
 * Let nums be the 0-indexed array of integers seen so far and nums_reverse be the reverse of nums,
 * then the integer at (k - 1)th index of nums_reverse will be the last visited integer for this
 * "prev".
 *
 * - If k is greater than the total visited integers, then the last visited integer will be -1.
 *
 * Return an integer array containing the last visited integers.
 *
 * ! 1 <= words.length <= 100
 * ! words[i] == "prev" or 1 <= int(words[i]) <= 100
 */

class Solution {
public:
    std::vector<int> lastVisitedIntegers(std::vector<std::string>& words)
    {
        std::vector<int> nums;
        int count = 0;
        std::vector<int> result;
        for (const auto& word : words) {
            if (word != "prev") {
                count = 0;
                nums.push_back(std::stoi(word));
                continue;
            }
            count++;
            result.push_back(nums.size() >= count ? nums[nums.size() - count] : -1);
        }
        return result;
    }
};