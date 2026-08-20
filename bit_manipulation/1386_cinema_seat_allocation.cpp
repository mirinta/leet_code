#include <unordered_map>
#include <vector>

/**
 * A cinema has n rows of seats, numbered from 1 to n and there are ten seats in each row, labelled from 1 to 10 as
 * shown in the figure above.
 *
 * Given the array reservedSeats containing the numbers of seats already reserved, for example, reservedSeats[i] = [3,8]
 * means the seat located in row 3 and labelled with 8 is already reserved.
 *
 * Return the maximum number of four-person groups you can assign on the cinema seats. A four-person group occupies four
 * adjacent seats in one single row. Seats across an aisle (such as [3,3] and [3,4]) are not considered to be adjacent,
 * but there is an exceptional case on which an aisle split a four-person group, in that case, the aisle split a
 * four-person group in the middle, which means to have two people on each side.
 *
 * ! 1 <= n <= 10^9
 * ! 1 <= reservedSeats.length <= min(10*n, 10^4)
 * ! reservedSeats[i].length == 2
 * ! 1 <= reservedSeats[i][0] <= n
 * ! 1 <= reservedSeats[i][1] <= 10
 * ! All reservedSeats[i] are distinct.
 */

class Solution {
public:
    int maxNumberOfFamilies(int n, std::vector<std::vector<int>>& reservedSeats)
    {
        // 9 8 7 | 6 5 4 3 | 2 1 0
        static constexpr int case1 = 15 << 1; // seats[1:4]
        static constexpr int case2 = 15 << 3; // seats[3:6]
        static constexpr int case3 = 15 << 5; // seats[5:8]
        static constexpr int case4 = case1 | case3;
        std::unordered_map<int, int> map;
        for (const auto& info : reservedSeats) {
            const auto& row = info[0] - 1;
            const auto& id = info[1] - 1;
            if (!map.count(row)) {
                map[row] = (1 << 10) - 1;
            }
            map[row] ^= (1 << id);
        }
        // each non-reserved row can assign at most two groups
        int result = 2 * (n - map.size());
        for (const auto& [r, mask] : map) {
            if ((mask & case4) == case4) {
                result += 2;
            } else if ((mask & case1) == case1 || (mask & case2) == case2 || (mask & case3) == case3) {
                result++;
            }
        }
        return result;
    }
};
