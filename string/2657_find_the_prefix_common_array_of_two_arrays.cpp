#include <vector>

/**
 * You are given two 0-indexed integer permutations A and B of length n.
 *
 * A prefix common array of A and B is an array C such that C[i] is equal to the count of numbers
 * that are present at or before the index i in both A and B.
 *
 * Return the prefix common array of A and B.
 *
 * A sequence of n integers is called a permutation if it contains all integers from 1 to n exactly
 * once.
 *
 * ! 1 <= A.length == B.length == n <= 50
 * ! 1 <= A[i], B[i] <= n
 * ! It is guaranteed that A and B are both a permutation of n integers.
 */

class Solution {
public:
    std::vector<int> findThePrefixCommonArray(std::vector<int>& A, std::vector<int>& B)
    {
        const int n = A.size();
        std::vector<int> result(n);
        std::vector<int> freq(n + 1);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                result[i] = result[i - 1];
            }
            if (++freq[A[i]] == 2) {
                result[i]++;
            }
            if (++freq[B[i]] == 2) {
                result[i]++;
            }
        }
        return result;
    }
};
