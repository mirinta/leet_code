#include <unordered_map>
#include <vector>

/**
 * Given an array of integers arr.
 *
 * We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).
 *
 * Let's define a and b as follows:
 *
 * - a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
 *
 * - b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
 *
 * Note that ^ denotes the bitwise-xor operation.
 *
 * Return the number of triplets (i, j and k) Where a == b.
 *
 * ! 1 <= arr.length <= 300
 * ! 1 <= arr[i] <= 10^8
 */

class Solution {
public:
    int countTriplets(std::vector<int>& arr)
    {
        return approach2(arr);
    }

private:
    int approach2(const std::vector<int>& arr)
    {
        // let XOR[i] = arr[0] ^ ... ^ arr[i]
        // if i, j, k is a valid triplet, where 0 <= i < j <= k < n
        // then a = XOR[i-1] ^ XOR[j-1] and b = XOR[j-1] ^ XOR[k]
        // a = b, i.e., a ^ b = 0 => XOR[i-1] ^ XOR[k] = 0

        // for each k:
        // let map[XOR[k]] = num of i such that XOR[i] ^ XOR[k] = 0
        // case 1: i = i1 + 1, j can be [i1+2:k], num of j = k - i1 - 1
        // case 2: i = i2 + 1, j can be [i2+2:k], num of j = k - i2 - 1
        // case 3: i = i3 + 1, j can be [i3+2:k], num of j = k - i3 - 1
        // ...
        // case m: i = im + 1, j can be [im+1:k], num of j = k - im - 1
        // thus, num of valid triplets = m * (k - 1) - (i1 + i2 + ... + im)
        const int n = arr.size();
        std::unordered_map<int, std::pair<int, int>> map;
        // base case:
        // i = 0, then j is in the range of [1:k], num of j = k
        // a ^ b = arr[0] ^ ... ^ arr[k] = XOR[k] = 0
        // m = 1 and i1 + ... + im = -1
        map[0] = {1, -1};
        int result = 0;
        for (int k = 0, XOR = 0; k < n; ++k) {
            XOR ^= arr[k];
            if (k > 0 && map.count(XOR)) {
                result += map[XOR].first * (k - 1) - map[XOR].second;
            }
            map[XOR].first++;
            map[XOR].second += k;
        }
        return result;
    }

    int approach1(const std::vector<int>& arr)
    {
        // let XOR[i] = arr[0] ^ arr[1] ^ ... ^ arr[i-1]
        // if i, j, k is a valid triplet, where i < j <= k
        // then a = XOR[j] ^ XOR[i] and b = XOR[k+1] ^ XOR[j]
        // a = b, i.e., a ^ b = 0 => XOR[i] ^ XOR[k+1] = 0

        // given i and k such that XOR[i] = XOR[k+1] and i < k
        // then j can be i+1,i+2,...,k => num of valid j = k-i
        const int n = arr.size();
        std::vector<int> XOR(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            XOR[i] = XOR[i - 1] ^ arr[i - 1];
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int k = i + 1; k < n; ++k) {
                if (XOR[i] == XOR[k + 1]) {
                    result += k - i;
                }
            }
        }
        return result;
    }
};