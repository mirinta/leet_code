#include <string>
#include <unordered_map>

/**
 * Given two arrays of strings list1 and list2, find the common strings with the least index sum.
 *
 * A common string is a string that appeared in both list1 and list2.
 *
 * A common string with the least index sum is a common string such that if it appeared at list1[i]
 * and list2[j] then i + j should be the minimum value among all the other common strings.
 *
 * Return all the common strings with the least index sum. Return the answer in any order.
 *
 * ! 1 <= list1.length, list2.length <= 1000
 * ! 1 <= list1[i].length, list2[i].length <= 30
 * ! list1[i] and list2[i] consist of spaces ' ' and English letters.
 * ! All the strings of list1 are unique.
 * ! All the strings of list2 are unique.
 * ! There is at least a common string between list1 and list2.
 */

class Solution {
public:
    std::vector<std::string> findRestaurant(std::vector<std::string>& list1, std::vector<std::string>& list2)
    {
        std::unordered_map<std::string, int> map;
        for (int i = 0; i < list1.size(); ++i) {
            map[list1[i]] = i;
        }
        int minIndexSum = INT_MAX;
        std::vector<std::string> result;
        for (int i = 0; i < list2.size(); ++i) {
            if (!map.count(list2[i]))
                continue;

            const int indexSum = i + map[list2[i]];
            if (indexSum < minIndexSum) {
                result.clear();
                minIndexSum = indexSum;
            }
            if (indexSum == minIndexSum) {
                result.push_back(list2[i]);
            }
        }
        return result;
    }
};