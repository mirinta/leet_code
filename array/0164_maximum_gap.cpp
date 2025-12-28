#include <vector>

/**
 * Given an integer array "nums", return the maximum difference between two successive elements in
 * its sorted form. If the array contains less than two elements, return 0.
 *
 * You must write an algorithm that runs in linear time and uses linear extra space.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 */

class Solution {
public:
    int maximumGap(const std::vector<int>& nums)
    {
        const int n = nums.size();
        if (n <= 2)
            return n == 2 ? std::abs(nums.front() - nums.back()) : 0;

        // step 1: find min and max
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& val : nums) {
            min = std::min(min, val);
            max = std::max(max, val);
        }
        if (min == max)
            return 0;

        // step 2: put elements in buckets
        // - bucket capacity is at least 1
        const int bucketSize = std::max(1, (max - min) / (n - 1));
        const int bucketNum = (max - min) / bucketSize + 1;
        struct Bucket {
            int minVal = INT_MAX;
            int maxVal = INT_MIN;
            bool isUsed = false;
        };
        std::vector<Bucket> buckets(bucketNum, Bucket{});
        for (const auto& val : nums) {
            const auto id = (val - min) / bucketSize;
            buckets[id].minVal = std::min(buckets[id].minVal, val);
            buckets[id].maxVal = std::max(buckets[id].maxVal, val);
            buckets[id].isUsed = true;
        }
        // step 3: find max gap between buckets
        int result = 0;
        int prevMax = min; // for the first round
        for (const auto& bucket : buckets) {
            if (!bucket.isUsed)
                continue;

            result = std::max(result, bucket.minVal - prevMax);
            prevMax = bucket.maxVal;
        }
        return result;
    }
};