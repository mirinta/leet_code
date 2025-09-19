#include <queue>
#include <unordered_map>
#include <vector>

/**
 * There is a task management system that allows users to manage their tasks, each associated with a
 * priority. The system should efficiently handle adding, modifying, executing, and removing tasks.
 *
 * Implement the TaskManager class:
 *
 * - TaskManager(vector<vector<int>>& tasks) initializes the task manager with a list of
 * user-task-priority triples. Each element in the input list is of the form [userId, taskId,
 * priority], which adds a task to the specified user with the given priority.
 *
 * - void add(int userId, int taskId, int priority) adds a task with the specified taskId and
 * priority to the user with userId. It is guaranteed that taskId does not exist in the system.
 *
 * - void edit(int taskId, int newPriority) updates the priority of the existing taskId to
 * newPriority. It is guaranteed that taskId exists in the system.
 *
 * - void rmv(int taskId) removes the task identified by taskId from the system. It is guaranteed
 * that taskId exists in the system.
 *
 * - int execTop() executes the task with the highest priority across all users. If there are
 * multiple tasks with the same highest priority, execute the one with the highest taskId. After
 * executing, the taskId is removed from the system. Return the userId associated with the executed
 * task. If no tasks are available, return -1.
 *
 * Note that a user may be assigned multiple tasks.
 *
 * ! 1 <= tasks.length <= 10^5
 * ! 0 <= userId <= 10^5
 * ! 0 <= taskId <= 10^5
 * ! 0 <= priority <= 10^9
 * ! 0 <= newPriority <= 10^9
 * ! At most 2 * 10^5 calls will be made in total to add, edit, rmv, and execTop methods.
 * ! The input is generated such that taskId will be valid.
 */

class TaskManager
{
public:
    TaskManager(std::vector<std::vector<int>>& tasks)
    {
        for (const auto& t : tasks) {
            pq.emplace(t[0], t[1], t[2], 0);
            map[t[1]] = {t[0], 0};
        }
    }

    void add(int userId, int taskId, int priority)
    {
        const int time = map.count(taskId) ? map[taskId].second + 1 : 0;
        pq.emplace(userId, taskId, priority, time);
        map[taskId] = {userId, time};
    }

    void edit(int taskId, int newPriority)
    {
        map[taskId].second++;
        pq.emplace(map[taskId].first, taskId, newPriority, map[taskId].second);
    }

    void rmv(int taskId) { map[taskId].second++; }

    int execTop()
    {
        while (!pq.empty() && pq.top().timestamp < map[pq.top().taskId].second) {
            pq.pop();
        }
        if (pq.empty())
            return -1;

        const int result = pq.top().userId;
        pq.pop();
        return result;
    }

private:
    struct Task
    {
        int userId{-1};
        int taskId{-1};
        int priority{-1};
        int timestamp{0};
    };

    struct Compare
    {
        bool operator()(const Task& t1, const Task& t2) const
        {
            return t1.priority != t2.priority ? t1.priority < t2.priority : t1.taskId < t2.taskId;
        }
    };

    std::unordered_map<int, std::pair<int, int>> map; // taskId to <userId, timestamp>
    std::priority_queue<Task, std::vector<Task>, Compare> pq;
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */