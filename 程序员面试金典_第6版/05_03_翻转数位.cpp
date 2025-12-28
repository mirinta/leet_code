#include <array>
#include <vector>

/**
 * 给定一个32位整数num，你可以将一个数位从0变为1。请编写一个程序，找出你能够获得的最长的一串1的长度。
 */

class Solution {
public:
    int reverseBits(int num)
    {
        return approach2(num);
    }

private:
    int approach2(int num)
    {
        int flipped = 1 - (num & 1);
        int notFlipped = num & 1;
        int result = 1;
        for (int i = 1; i < 32; ++i) {
            if ((num >> i) & 1) {
                notFlipped += 1;
                flipped += 1;
            } else {
                flipped = 1 + notFlipped;
                notFlipped = 0;
            }
            result = std::max({result, flipped, notFlipped});
        }
        return result;
    }

    int approach1(int num)
    {
        std::array<int, 32> bits{};
        for (int i = 0; i < 32; ++i) {
            if ((num >> i) & 1) {
                bits[i] = 1;
            }
        }
        // dp[i][0] = max num of consecutive 1's of bits[0:i] ending at nums[i] without any flipped
        // element dp[i][1] = max num of consecutive 1's of bits[0:i] ending at nums[i] with exactly
        // one flipped element
        std::array<std::array<int, 2>, 32> dp{{0, 0}};
        dp[0][1 - bits[0]] = 1;
        int result = 1;
        for (int i = 1; i < 32; ++i) {
            if (bits[i] == 1) {
                dp[i][0] = 1 + dp[i - 1][0];
                dp[i][1] = 1 + dp[i - 1][1];
            } else {
                dp[i][0] = 0;
                dp[i][1] = 1 + dp[i - 1][0];
            }
            result = std::max({result, dp[i][0], dp[i][1]});
        }
        return result;
    }
};