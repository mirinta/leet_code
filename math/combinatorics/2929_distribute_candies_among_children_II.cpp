#include <algorithm>

/**
 * You are given two positive integers n and limit.
 *
 * Return the total number of ways to distribute n candies among 3 children such that no child gets
 * more than limit candies.
 *
 * ! 1 <= n <= 50
 * ! 1 <= limit <= 50
 */

class Solution {
public:
    long long distributeCandies(int n, int limit)
    {
        return approach2(n, limit);
    }

private:
    long long approach2(int n, int limit)
    {
        // answer = total - #invalid cases
        // total = C(n+2, 2)
        // #invalid cases = |A∪B∪C| = |A| + |B| + |C| - (|A∩B| + |A∩C| + |B∩C|) + |A∩B∩C|
        // |A| = |B| = |C| = one child takes at least limit+1 candies, C(n-(limit+1)+2,2)
        // |A∩B| = |A∩C| = |B∩C| = two children takes at least limit+1 candies, C(n-2*(limit+1)+2,2)
        // |A∩B∩C| = three children takes at least limit+1 candies, C(n-3*(limit+1)+2, 2)
        long long result = combination2(n + 2);
        result -= 3 * combination2(n - limit + 1);
        result += 3 * combination2(n - 2 * limit);
        result -= combination2(n - 3 * limit - 1);
        return result;
    }

    long long combination2(long long n)
    {
        return n > 1 ? n * (n - 1) / 2 : 0;
    }

    long long approach1(int n, int limit)
    {
        if (n > 3 * limit)
            return 0;

        const int minOfA = std::max(0, n - 2 * limit); // let B and C take limit candies
        const int maxOfA = std::min(limit, n);
        long long result = 0;
        for (int A = minOfA; A <= maxOfA; ++A) {
            const int minOfB = std::max(0, n - A - limit); // let C take limit candies
            const int maxOfB = std::min(limit, n - A);
            // since A is fixed,
            // for each B in the range [minOfB, maxOfB], C can be determined
            result += maxOfB - minOfB + 1;
        }
        return result;
    }
};
