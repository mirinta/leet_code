#include <random>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer "n" and an array of unique integers "blacklist". Design an algorithm to
 * pick a random integer in the range [0, n - 1] that is not in "blacklist". Any integer that is in
 * the mentioned range and not in "blacklist" should be equally likely to be returned.
 *
 * Optimize your algorithm such that it minimizes the number of calls to the built-in random
 * function of your language.
 *
 * Implement the "Solution" class:
 *
 * - "Solution(int n, int [] blacklist)" initializes the object with the integer "n" and the
 * blacklisted integers "blacklist".
 *
 * - "int pick()" returns a random integer in the range [0, n - 1] and not in "blacklist".
 */

class Solution {
    // let n = 5, then the picking range is [0, 1, 2, 3, 4]
    // let blacklist = [0, 1], then the whitelist is [2, 3, 4]
    // map 0 to 4, and map 1 to 3
private:
    int whitelistSize = 0;            // n - blacklist.size()
    std::unordered_map<int, int> map; // index of blacklist to index of whitelist
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distribution;

public:
    Solution(int n, const std::vector<int>& blacklist)
        : whitelistSize(n - blacklist.size()), gen(rd()), distribution(0, whitelistSize - 1)
    {
        // store all blacklist numbers
        for (const auto& i : blacklist) {
            map[i] = -1;
        }
        // if X is in the blacklist, map it to the last number of the whitelist
        int last = n - 1;
        for (const auto& i : blacklist) {
            if (i >= whitelistSize)
                continue;

            while (map.count(last)) {
                last--;
            }
            map[i] = last;
            last--;
        }
    }

    int pick()
    {
        const auto index = distribution(gen);
        if (map.count(index))
            return map[index];

        return index;
    }
};

/**
 * Your Solution object will be initialized and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */