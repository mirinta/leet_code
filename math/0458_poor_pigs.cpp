#include <cmath>

/**
 * There are buckets buckets of liquid, where exactly one of the buckets is poisonous. To figure out
 * which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will
 * die or not. Unfortunately, you only have minutesToTest minutes to determine which bucket is
 * poisonous.
 *
 * You can feed the pigs according to these steps:
 *
 * 1. Choose some live pigs to feed.
 *
 * 2. For each pig, choose which buckets to feed it. The pig will consume all the chosen buckets
 * simultaneously and will take no time. Each pig can feed from any number of buckets, and each
 * bucket can be fed from by any number of pigs.
 *
 * 3. Wait for minutesToDie minutes. You may not feed any other pigs during this time.
 *
 * 4. After minutesToDie minutes have passed, any pigs that have been fed the poisonous bucket will
 * die, and all others will survive.
 *
 * 5. Repeat this process until you run out of time.
 *
 * Given buckets, minutesToDie, and minutesToTest, return the minimum number of pigs needed to
 * figure out which bucket is poisonous within the allotted time.
 *
 * ! 1 <= buckets <= 1000
 * ! 1 <= minutesToDie <= minutesToTest <= 100
 */

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest)
    {
        // #states = 1 + totalTime / waitTime
        // - e.g., if totalTime / waitTime = 1, we only have one experiment
        //   then each has two states {alive, dead}
        // #buckets = #states ^ #pigs
        const int states = minutesToTest / minutesToDie + 1;
        return std::ceil(std::log2(buckets) / std::log2(states));
    }
};