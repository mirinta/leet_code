#include <algorithm>
#include <vector>

/**
 * You are given an array tasks where tasks[i] = [actuali, minimumi]:
 *
 * - actuali is the actual amount of energy you spend to finish the ith task,
 *
 * - minimumi is the minimum amount of energy you require to begin the ith task.
 *
 * For example, if the task is [10, 12] and your current energy is 11, you cannot start this task. However, if your
 * current energy is 13, you can complete this task, and your energy will be 3 after finishing it.
 *
 * You can finish the tasks in any order you like.
 *
 * Return the minimum initial amount of energy you will need to finish all the tasks.
 *
 * ! 1 <= tasks.length <= 10^5
 * ! 1 <= actuali <= minimumi <= 10^4
 */

class Solution {
public:
    int minimumEffort(std::vector<std::vector<int>>& tasks)
    {
        // task1(a1, m1), task2(a2, m2)
        // E = current energy
        //
        // case1: task1 before task2
        // E >= m1 && E - a1 >= m2
        // thus, E >= max(m1, m2 + a1)
        //
        // case2: task2 before task1
        // E >= m2 && E - a2 >= m1
        // thus, E >= max(m2, m1 + a2)
        //
        // if case1 is better than case2, then
        // max(m1, m2 + a1) <= max(m2, m1 + a2)
        // max(m1 - a1 - a2, m2 - a2) <= max(m2 - a1 - a2, m1 - a1)
        //
        // let P1 = m1 - a1, P2 = m2 - a2
        // max(P1 - a2, P2) <= max(P2 - a1, P1)
        //
        // assumption: P1 < P2
        // then left side = P2, right side < P2, assumption is not true
        //
        // assumption: P1 >= P2
        // then left side <= P2, right side = P1, assumption is true
        //
        // therefore, case1 is better than case2 iff (m1 - a1) >= (m2 - a2)
        std::sort(tasks.begin(), tasks.end(),
                  [](const auto& t1, const auto& t2) { return t1[1] - t1[0] > t2[1] - t2[0]; });
        const int n = tasks.size();
        int result = 0;
        for (int i = n - 1; i >= 0; --i) {
            result = std::max(result + tasks[i][0], tasks[i][1]);
        }
        return result;
    }
};
