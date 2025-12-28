#include <array>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: 0, 1, 2, 3, 4,
 * 5, 6, 7, 8, 9. The wheels can rotate freely and wrap around: for example we can turn 9 to be 0,
 * or 0 to be 9. Each move consists of turning one wheel one slot.
 *
 * The lock initially starts at 0000, a string representing the state of the 4 wheels.
 *
 * You are given a list of "deadends" dead ends, meaning if the lock display any of these codes, the
 * wheels of the lock will stop turning and you will be unable to open it.
 *
 * Given a "target" representing the value of the wheels that will unlock the lock, return the
 * minimum total number of turns required to open the lock, or -1 if it is impossible.
 *
 * ! Constraints:
 * ! - deadends[i].length == 4
 * ! - target.length == 4
 * ! - "target" will not be in the list "deadends".
 * ! - "target" and "deadends[i]" consist of digits only.
 */

class Solution {
public:
    int openLock(std::vector<std::string>& deadends, std::string target)
    {
        const std::string src("0000");
        std::unordered_set<std::string> visited(deadends.begin(), deadends.end());
        if (visited.count(src))
            return -1;

        constexpr std::array<int, 2> directions{1, -1};
        visited.insert(src);
        std::queue<std::string> queue;
        queue.push(src);
        int result = -1;
        while (!queue.empty()) {
            result++;
            for (int k = queue.size(); k > 0; --k) {
                const auto curr = queue.front();
                queue.pop();
                if (curr == target)
                    return result;

                for (int wheel = 0; wheel < 4; ++wheel) {
                    for (const auto& d : directions) {
                        const auto next = rotate(curr, wheel, d);
                        if (!visited.count(next)) {
                            visited.insert(next);
                            queue.push(next);
                        }
                    }
                }
            }
        }
        return -1;
    }

private:
    std::string rotate(const std::string& s, int i, int delta)
    {
        auto result(s);
        result[i] = (s[i] - '0' + delta + 10) % 10 + '0';
        return result;
    }
};