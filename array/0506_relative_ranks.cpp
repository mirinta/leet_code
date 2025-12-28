#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array score of size n, where score[i] is the score of the ith athlete in
 * a competition. All the scores are guaranteed to be unique.
 *
 * The athletes are placed based on their scores, where the 1st place athlete has the highest score,
 * the 2nd place athlete has the 2nd highest score, and so on. The placement of each athlete
 * determines their rank:
 *
 * - The 1st place athlete's rank is "Gold Medal".
 *
 * - The 2nd place athlete's rank is "Silver Medal".
 *
 * - The 3rd place athlete's rank is "Bronze Medal".
 *
 * - For the 4th place to the nth place athlete, their rank is their placement number (i.e., the xth
 * place athlete's rank is "x").
 *
 * Return an array answer of size n where answer[i] is the rank of the ith athlete.
 *
 * ! n == score.length
 * ! 1 <= n <= 10^4
 * ! 0 <= score[i] <= 10^6
 * ! All the values in score are unique.
 */

class Solution {
public:
    std::vector<std::string> findRelativeRanks(std::vector<int>& score)
    {
        const int n = score.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            map[score[i]] = i;
        }
        std::sort(score.begin(), score.end(), std::greater<>());
        std::vector<std::string> result(n, " ");
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                result[map[score[i]]] = "Gold Medal";
            } else if (i == 1) {
                result[map[score[i]]] = "Silver Medal";
            } else if (i == 2) {
                result[map[score[i]]] = "Bronze Medal";
            } else {
                result[map[score[i]]] = std::to_string(i + 1);
            }
        }
        return result;
    }
};