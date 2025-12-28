/**
 * Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.
 *
 * He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will
 * put in $1 more than the day before. On every subsequent Monday, he will put in $1 more than the
 * previous Monday.
 *
 * Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth
 * day.
 *
 * ! 1 <= n <= 1000
 */

class Solution {
public:
    int totalMoney(int n)
    {
        int result = 0;
        int monday = 1;
        for (int week = 0; week < n / 7; ++week) {
            monday++;
            result += 28 + week * 7; // 28=1+2+...+7
        }
        result += (monday + monday + n % 7 - 1) * (n % 7) / 2;
        return result;
    }
};