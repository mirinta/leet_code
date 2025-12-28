#include <unordered_map>
#include <vector>

/**
 * You have n processes forming a rooted tree structure. You are given two integer arrays pid and
 * ppid, where pid[i] is the ID of the ith process and ppid[i] is the ID of the ith process's parent
 * process.
 *
 * Each process has only one parent process but may have multiple children processes. Only one
 * process has ppid[i] = 0, which means this process has no parent process (the root of the tree).
 *
 * When a process is killed, all of its children processes will also be killed.
 *
 * Given an integer kill representing the ID of a process you want to kill, return a list of the IDs
 * of the processes that will be killed. You may return the answer in any order.
 *
 * ! n == pid.length
 * ! n == ppid.length
 * ! 1 <= n <= 5 * 104
 * ! 1 <= pid[i] <= 5 * 104
 * ! 0 <= ppid[i] <= 5 * 104
 * ! Only one process has no parent.
 * ! All the values of pid are unique.
 * ! kill is guaranteed to be in pid.
 */

class Solution {
public:
    std::vector<int> killProcess(std::vector<int>& pid, std::vector<int>& ppid, int kill)
    {
        const int n = pid.size();
        std::unordered_map<int, std::vector<int>> graph;
        for (int i = 0; i < n; ++i) {
            graph[ppid[i]].push_back(pid[i]);
        }
        std::vector<int> result;
        dfs(result, kill, graph);
        return result;
    }

private:
    void dfs(std::vector<int>& result, int root, const std::unordered_map<int, std::vector<int>>& graph)
    {
        result.push_back(root);
        if (!graph.count(root))
            return;

        for (const auto& child : graph.at(root)) {
            dfs(result, child, graph);
        }
    }
};