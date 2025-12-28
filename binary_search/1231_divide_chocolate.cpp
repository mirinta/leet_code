#include <numeric>
#include <vector>

/**
 * You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given
 * by the array sweetness.
 *
 * You want to share the chocolate with your k friends so you start cutting the chocolate bar into k
 * + 1 pieces using k cuts, each piece consists of some consecutive chunks.
 *
 * Being generous, you will eat the piece with the minimum total sweetness and give the other pieces
 * to your friends.
 *
 * Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.
 *
 * ! 0 <= k < sweetness.length <= 10^4
 * ! 1 <= sweetness[i] <= 10^5
 */

class Solution {
public:
    int maximizeSweetness(std::vector<int>& sweetness, int k)
    {
        int lo = 1;
        int hi = std::accumulate(sweetness.begin(), sweetness.end(), 0);
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, sweetness, k + 1)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int minGain, const std::vector<int>& sweetness, int minGroups)
    {
        // everyone takes >= minGain, then I can always choose the minimum gain
        int count = 0;
        int sum = 0;
        for (const auto& val : sweetness) {
            sum += val;
            if (sum >= minGain) {
                sum = 0;
                count++;
            }
            if (count >= minGroups)
                return true;
        }
        return false;
    }
};
