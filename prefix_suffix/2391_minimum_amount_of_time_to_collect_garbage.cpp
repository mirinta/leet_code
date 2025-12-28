#include <string>
#include <vector>

/**
 * You are given a 0-indexed array of strings garbage where garbage[i] represents the assortment of
 * garbage at the ith house. garbage[i] consists only of the characters 'M', 'P' and 'G'
 * representing one unit of metal, paper and glass garbage respectively. Picking up one unit of any
 * type of garbage takes 1 minute.
 *
 * You are also given a 0-indexed integer array travel where travel[i] is the number of minutes
 * needed to go from house i to house i + 1.
 *
 * There are three garbage trucks in the city, each responsible for picking up one type of garbage.
 * Each garbage truck starts at house 0 and must visit each house in order; however, they do not
 * need to visit every house.
 *
 * Only one garbage truck may be used at any given moment. While one truck is driving or picking up
 * garbage, the other two trucks cannot do anything.
 *
 * Return the minimum number of minutes needed to pick up all the garbage.
 *
 * ! 2 <= garbage.length <= 10^5
 * ! garbage[i] consists of only the letters 'M', 'P', and 'G'.
 * ! 1 <= garbage[i].length <= 10
 * ! travel.length == garbage.length - 1
 * ! 1 <= travel[i] <= 100
 */

class Solution {
public:
    int garbageCollection(std::vector<std::string>& garbage, std::vector<int>& travel)
    {
        std::vector<int> prefix(travel.size() + 1);
        for (int i = 1; i < prefix.size(); ++i) {
            prefix[i] = prefix[i - 1] + travel[i - 1];
        }
        int result = 0;
        for (const auto& s : garbage) {
            result += s.size();
        }
        constexpr char kGarbageTypes[] = "PMG";
        for (const auto& c : kGarbageTypes) {
            result += prefix[std::max(0, findLast(c, garbage))];
        }
        return result;
    }

private:
    int findLast(char c, const std::vector<std::string>& garbage)
    {
        for (int i = garbage.size() - 1; i >= 0; --i) {
            if (const auto idx = garbage[i].find(c); idx != std::string::npos)
                return i;
        }
        return -1;
    }
};