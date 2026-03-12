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
        static constexpr int mask1 = 15 << 3;       // seats[3:6], 0-indexed
        static constexpr int mask2 = 15 << 5;       // seats[6:9], 0-indexed
        static constexpr int mask3 = 15 << 1;       // seats[1:4], 0-indexed
        static constexpr int mask4 = mask2 | mask3; // seats[1:8], 0-indexed
        std::unordered_map<int, std::vector<int>> map;
        for (const auto& s : reservedSeats) {
            map[s[0]].emplace_back(s[1]);
        }
        int result = (n - map.size()) * 2;
        for (const auto& [row, seats] : map) {
            int mask = (1 << 10) - 1;
            for (const auto& i : seats) {
                mask ^= 1 << (i - 1);
            }
            if (!((mask & mask4) ^ mask4)) {
                result += 2;
            } else if (!((mask & mask1) ^ mask1) || !((mask & mask2) ^ mask2) || !((mask & mask3) ^ mask3)) {
                result++;
            }
        }
        return result;
    }
};
