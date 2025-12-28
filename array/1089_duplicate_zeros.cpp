#include <vector>

/**
 * Given a fixed-length integer array "arr", duplicate each occurrence of zero, shifting the
 * remaining elements to the right.
 *
 * Note that elements beyond the length of the original array are not written. Do the above
 * modification to the input array in place and do not return anything.
 */

class Solution {
public:
    void duplicateZeros(std::vector<int>& arr)
    {
        if (arr.empty())
            return;

        int zeros = 0;
        for (const auto& i : arr) {
            if (i == 0) {
                zeros++;
            }
        }
        for (int i = arr.size() - 1; i >= 0; --i) {
            if (!arr[i]) {
                zeros--;
            }
            if (i + zeros < arr.size()) {
                arr[i + zeros] = arr[i];
                if (!arr[i] && i + zeros + 1 < arr.size()) {
                    arr[i + zeros + 1] = 0;
                }
            }
        }
    }
};