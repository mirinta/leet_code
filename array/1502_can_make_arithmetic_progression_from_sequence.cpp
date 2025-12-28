#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * A sequence of numbers is called an arithmetic progression if the difference between any two
 * consecutive elements is the same.
 *
 * Given an array of numbers "arr", return true if the array can be rearranged to from an arithmetic
 * progression. Otherwise, return false;
 */

class Solution {
public:
    bool canMakeArithmeticProgression(std::vector<int>& arr)
    {
        return approach3(arr);
    }

private:
    bool approach1(std::vector<int>& arr)
    {
        if (arr.size() < 2)
            return false;

        std::sort(arr.begin(), arr.end());
        for (size_t i = 1; i < arr.size() - 1; ++i) {
            if (arr[i] - arr[i - 1] != arr[i + 1] - arr[i])
                return false;
        }
        return true;
    }

    bool approach2(const std::vector<int>& arr)
    {
        if (arr.size() < 2)
            return false;

        int min = INT_MAX;
        int max = INT_MIN;
        const int n = arr.size();
        for (const auto& val : arr) {
            min = std::min(min, val);
            max = std::max(max, val);
        }
        if (min == max)
            return true;

        if ((max - min) % (n - 1) != 0)
            return false;

        const int diff = (max - min) / (n - 1);
        std::unordered_set<int> set;
        for (const auto& val : arr) {
            if ((val - min) % diff != 0)
                return false;

            set.emplace(val);
        }
        return set.size() == n;
    }

    bool approach3(std::vector<int>& arr)
    {
        if (arr.size() < 2)
            return false;

        int min = INT_MAX;
        int max = INT_MIN;
        const int n = arr.size();
        for (const auto& val : arr) {
            min = std::min(min, val);
            max = std::max(max, val);
        }
        if (min == max)
            return true;

        if ((max - min) % (n - 1) != 0)
            return false;

        const int diff = (max - min) / (n - 1);
        int i = 0;
        while (i < n) {
            if (arr[i] == min + diff * i) {
                i++;
                continue;
            }
            if ((arr[i] - min) % diff != 0)
                return false;

            const int pos = (arr[i] - min) / diff;
            if (arr[pos] == arr[i])
                return false;

            std::swap(arr[pos], arr[i]);
        }
        return true;
    }
};
