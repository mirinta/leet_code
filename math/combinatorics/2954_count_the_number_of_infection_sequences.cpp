#include <vector>

/**
 * You are given an integer n and a 0-indexed integer array sick which is sorted in increasing
 * order.
 *
 * There are n children standing in a queue with positions 0 to n - 1 assigned to them. The array
 * sick contains the positions of the children who are infected with an infectious disease. An
 * infected child at position i can spread the disease to either of its immediate neighboring
 * children at positions i - 1 and i + 1 if they exist and are currently not infected. At most one
 * child who was previously not infected can get infected with the disease in one second.
 *
 * It can be shown that after a finite number of seconds, all the children in the queue will get
 * infected with the disease. An infection sequence is the sequential order of positions in which
 * all of the non-infected children get infected with the disease. Return the total number of
 * possible infection sequences.
 *
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * Note that an infection sequence does not contain positions of children who were already infected
 * with the disease in the beginning.
 *
 * ! 2 <= n <= 10^5
 * ! 1 <= sick.length <= n - 1
 * ! 0 <= sick[i] <= n - 1
 * ! sick is sorted in increasing order.
 */

class Solution {
public:
    int numberOfSequence(int n, std::vector<int>& sick)
    {
        std::vector<long long> factorial(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            factorial[i] = factorial[i - 1] * i % kMod;
        }
        std::vector<long long> inv_factorial(n + 1);
        inv_factorial[n] = powmod(factorial[n], kMod - 2);
        for (int i = n - 1; i >= 0; --i) {
            inv_factorial[i] = inv_factorial[i + 1] * (i + 1) % kMod;
        }
        auto combination = [&](int n, int k) {
            return factorial[n] * inv_factorial[k] % kMod * inv_factorial[n - k] % kMod;
        };
        // X are infected children and H are healthy children.
        // Infected children divides the given array into sevral groups of health children.
        // H .... H X H .... H X H .... H X H .... H
        // |<-g1->|   |<-g2->|   |<-g3->|   |<-g4->|
        std::vector<int> groups;
        for (int i = 0, prev = -1; i < sick.size(); ++i) {
            groups.push_back(sick[i] - prev - 1);
            prev = sick[i];
        }
        groups.push_back(n - sick.back() - 1);
        int total = n - sick.size();
        long long result = 1;
        for (int i = 0; i < groups.size(); ++i) {
            if (groups[i] == 0)
                continue;

            result = result * combination(total, groups[i]) % kMod;
            if (i > 0 && i < groups.size() - 1) {
                result = result * powmod(2, groups[i] - 1) % kMod;
            }
            total -= groups[i];
        }
        return result;
    }

private:
    static constexpr int kMod = 1e9 + 7;

    long long powmod(long long a, long long b)
    {
        long long result = 1;
        long long base = a;
        while (b > 0) {
            if (b & 1) {
                result = result * base % kMod;
            }
            base = base * base % kMod;
            b >>= 1;
        }
        return result;
    }
};