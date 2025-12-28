#include <algorithm>
#include <vector>

/**
 * You are given a series of video clips from a sporting event that lasted time seconds. These video
 * clips can be overlapping with each other and have varying lengths.
 *
 * Each video clip is described by an array clips where clips[i] = [starti, endi] indicates that the
 * ith clip started at starti and ended at endi.
 *
 * We can cut these clips into segments freely.
 *
 * - For example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
 *
 * Return the minimum number of clips needed so that we can cut the clips into segments that cover
 * the entire sporting event [0, time]. If the task is impossible, return -1.
 *
 * ! 1 <= clips.length <= 100
 * ! 0 <= starti <= endi <= 100
 * ! 1 <= time <= 100
 */

class Solution {
public:
    int videoStitching(std::vector<std::vector<int>>& clips, int time)
    {
        std::sort(clips.begin(), clips.end(),
                  [](const auto& v1, const auto& v2) { return v1[0] == v2[0] ? v1[1] > v2[1] : v1[0] < v2[0]; });
        if (clips[0][0] != 0)
            return -1;

        if (clips[0][1] >= time)
            return 1;

        int end = clips[0][1];
        int i = 0;
        int result = 1; // take the first one into account
        while (i < clips.size()) {
            int maxEnd = end;
            while (i < clips.size() && clips[i][0] <= end) {
                maxEnd = std::max(maxEnd, clips[i][1]);
                i++;
            }
            if (maxEnd == end)
                return -1;

            result++;
            if (maxEnd >= time)
                return result;

            end = maxEnd;
        }
        return -1;
    }
};