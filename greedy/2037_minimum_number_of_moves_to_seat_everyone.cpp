#include <algorithm>
#include <vector>

/**
 * There are n seats and n students in a room. You are given an array seats of length n, where
 * seats[i] is the position of the ith seat. You are also given the array students of length n,
 * where students[j] is the position of the jth student.
 *
 * You may perform the following move any number of times:
 *
 * Increase or decrease the position of the ith student by 1 (i.e., moving the ith student from
 * position x to x + 1 or x - 1) Return the minimum number of moves required to move each student to
 * a seat such that no two students are in the same seat.
 *
 * Note that there may be multiple seats or students in the same position at the beginning.
 *
 * ! n == seats.length == students.length
 * ! 1 <= n <= 100
 * ! 1 <= seats[i], students[j] <= 100
 */

class Solution {
public:
    int minMovesToSeat(std::vector<int>& seats, std::vector<int>& students)
    {
        const int n = seats.size();
        std::sort(seats.begin(), seats.end());
        std::sort(students.begin(), students.end());
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += std::abs(seats[i] - students[i]);
        }
        return result;
    }
};