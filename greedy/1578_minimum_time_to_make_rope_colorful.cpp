#include <string>
#include <vector>

/**
 * Alice has n balloons arranged on a rope. You are given a 0-indexed string colors where colors[i]
 * is the color of the ith balloon.
 *
 * Alice wants the rope to be colorful. She does not want two consecutive balloons to be of the same
 * color, so she asks Bob for help. Bob can remove some balloons from the rope to make it colorful.
 * You are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds)
 * that Bob needs to remove the ith balloon from the rope.
 *
 * Return the minimum time Bob needs to make the rope colorful.
 *
 * ! n == colors.length == neededTime.length
 * ! 1 <= n <= 10^5
 * ! 1 <= neededTime[i] <= 10^4
 * ! colors contains only lowercase English letters.
 */

class Solution {
public:
    int minCost(std::string colors, std::vector<int>& neededTime)
    {
        // find substring colors[i:j], all colors in this substring are the same
        // assume its length is L and we need to remove L-1 balloons with minimum cost
        const int n = colors.size();
        int result = 0;
        int i = 0;
        while (i < n) {
            int totalTime = neededTime[i];
            int maxTime = neededTime[i];
            int j = i + 1;
            while (j < n && colors[j] == colors[i]) {
                maxTime = std::max(maxTime, neededTime[j]);
                totalTime += neededTime[j];
                j++;
            }
            result += totalTime - maxTime;
            i = j;
        }
        return result;
    }
};