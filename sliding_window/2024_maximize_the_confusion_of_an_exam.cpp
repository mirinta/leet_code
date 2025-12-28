#include <string>

/**
 * A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting
 * false. He wants to confuse the students by maximizing the number of consecutive questions with
 * the same answer (multiple trues or multiple falses in a row).
 *
 * You are given a string answerKey, where answerKey[i] is the original answer to the ith question.
 * In addition, you are given an integer k, the maximum number of times you may perform the
 * following operation:
 *
 * - Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').
 *
 * Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the
 * operation at most k times.
 *
 * ! n == answerKey.length
 * ! 1 <= n <= 5 * 10^4
 * ! answerKey[i] is either 'T' or 'F'
 * ! 1 <= k <= n
 */

class Solution {
public:
    int maxConsecutiveAnswers(std::string answerKey, int k)
    {
        return approach2(answerKey, k);
    }

private:
    // sliding window (one-pass), TC = O(N), SC = O(1)
    int approach2(const std::string& answerKey, int k)
    {
        const int n = answerKey.size();
        int countF = 0;
        int countT = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            if (answerKey[right] == 'T') {
                countT++;
            } else {
                countF++;
            }
            while (std::min(countT, countF) > k) {
                if (answerKey[left] == 'T') {
                    countT--;
                } else {
                    countF--;
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }

    // sliding window (two-pass), TC = O(N), SC = O(1)
    int approach1(const std::string& answerKey, int k)
    {
        return std::max(solve(answerKey, k, 'T'), solve(answerKey, k, 'F'));
    }

    // return length of the longest substring of s such that
    // it contains the max num of consecutive x's after
    // applying at most k times of chaning operations
    int solve(const std::string& s, int k, char x)
    {
        const int n = s.size();
        int opposite = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            opposite += s[right] != x;
            while (opposite > k) {
                opposite -= s[left] != x;
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};