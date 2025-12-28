#include <climits>
#include <numeric>
#include <vector>

/**
 * Given a binary array data, return the minimum number of swaps required to group all 1’s present
 * in the array together in any place in the array.
 *
 * ! 1 <= data.length <= 10^5
 * ! data[i] is either 0 or 1.
 */

class Solution {
public:
    int minSwaps(std::vector<int>& data)
    {
        const int n = data.size();
        const int totalOnes = std::accumulate(data.begin(), data.end(), 0);
        int result = INT_MAX;
        for (int left = 0, right = 0, sum = 0; right < n; ++right) {
            sum += data[right];
            if (right >= totalOnes) {
                sum -= data[left++];
            }
            result = std::min(result, totalOnes - sum);
        }
        return result;
    }
};
