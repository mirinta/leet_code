#include <string>
#include <vector>

/**
 * A permutation perm of n integers of all the integers in the range [1, n] can be represented as a
 * string s of length n - 1 where:
 *
 * - s[i] == 'I' if perm[i] < perm[i + 1], and
 *
 * - s[i] == 'D' if perm[i] > perm[i + 1].
 *
 * Given a string s, reconstruct the lexicographically smallest permutation perm and return it.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either 'I' or 'D'.
 */

class Solution {
public:
    std::vector<int> findPermutation(std::string s)
    {
        // let N = 5, then the smallest permutation and its pattern:
        //   I I I I
        // 1 2 3 4 5
        // consider the following pattern:
        //   I D D I
        // 1 2 3 4 5
        //   |<->| reverse
        // 1 4 3 2 5
        s.insert(s.begin(), 'I');
        const int n = s.size();
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = i + 1;
        }
        // find s[i:j] = IDD...D and reverse result[i:j]
        int i = 0;
        while (i < n) {
            while (i < n && s[i] == 'I') {
                i++;
            }
            int j = i;
            while (j < n && s[j] == 'D') {
                j++;
            }
            if (j > i - 1) {
                // s[i-1:j) is IDD...D
                std::reverse(std::prev(result.begin() + i), result.begin() + j);
                i = j;
            } else {
                i++;
            }
        }
        return result;
    }
};
