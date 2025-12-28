#include <string>
#include <vector>

/**
 * You are given an array of strings arr. A string s is formed by the concatenation of a subsequence
 * of arr that has unique characters.
 *
 * Return the maximum possible length of s.
 *
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 1 <= arr.length <= 16
 * ! 1 <= arr[i].length <= 26
 * ! arr[i] contains only lowercase English letters.
 */

class Solution {
public:
    int maxLength(std::vector<std::string>& arr)
    {
        const int n = arr.size();
        std::vector<int> masks(n, 0);
        for (int i = 0; i < n; ++i) {
            masks[i] = getMask(arr[i]);
        }
        return dfs(0, 0, masks, arr);
    }

private:
    int dfs(int i, int state, const std::vector<int>& masks, const std::vector<std::string>& arr)
    {
        if (i == arr.size())
            return numOfBinaryOnes(state);

        int result = dfs(i + 1, state, masks, arr);
        if (masks[i] && (state & masks[i]) == 0) {
            // arr[i] contains unique letters
            // and there's no intersection between mask[i] and current state
            result = std::max(result, dfs(i + 1, state | masks[i], masks, arr));
        }
        return result;
    }

    int getMask(const std::string& s)
    {
        int mask = 0;
        for (const auto& c : s) {
            if ((mask >> (c - 'a')) & 1)
                return 0; // found duplicates

            mask |= 1 << (c - 'a');
        }
        return mask;
    }

    int numOfBinaryOnes(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};