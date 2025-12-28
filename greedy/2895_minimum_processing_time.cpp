#include <algorithm>
#include <vector>

/**
 * You have n processors each having 4 cores and n * 4 tasks that need to be executed such that each
 * core should perform only one task.
 *
 * Given a 0-indexed integer array processorTime representing the time at which each processor
 * becomes available for the first time and a 0-indexed integer array tasks representing the time it
 * takes to execute each task, return the minimum time when all of the tasks have been executed by
 * the processors.
 *
 * Note: Each core executes the task independently of the others.
 *
 * ! 1 <= n == processorTime.length <= 25000
 * ! 1 <= tasks.length <= 10^5
 * ! 0 <= processorTime[i] <= 10^9
 * ! 1 <= tasks[i] <= 10^9
 * ! tasks.length == 4 * n
 */

class Solution {
public:
    int minProcessingTime(std::vector<int>& processorTime, std::vector<int>& tasks)
    {
        std::sort(processorTime.begin(), processorTime.end());
        std::sort(tasks.begin(), tasks.end());
        int result = 0;
        for (int i = 0, j = tasks.size() - 1; i < processorTime.size(); ++i, j -= 4) {
            result = std::max(result, processorTime[i] + tasks[j]);
        }
        return result;
    }
};