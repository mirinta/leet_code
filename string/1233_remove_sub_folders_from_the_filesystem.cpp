#include <algorithm>
#include <string>
#include <vector>

/**
 * Given a list of folders folder, return the folders after removing all sub-folders in those
 * folders. You may return the answer in any order.
 *
 * If a folder[i] is located within another folder[j], it is called a sub-folder of it. A sub-folder
 * of folder[j] must start with folder[j], followed by a "/". For example, "/a/b" is a sub-folder of
 * "/a", but "/b" is not a sub-folder of "/a/b/c".
 *
 * The format of a path is one or more concatenated strings of the form: '/' followed by one or more
 * lowercase English letters.
 *
 * For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string and "/"
 * are not.
 *
 * ! 1 <= folder.length <= 4 * 10^4
 * ! 2 <= folder[i].length <= 100
 * ! folder[i] contains only lowercase letters and '/'.
 * ! folder[i] always starts with the character '/'.
 * ! Each folder name is unique.
 */

class Solution {
public:
    std::vector<std::string> removeSubfolders(std::vector<std::string>& folder)
    {
        std::sort(folder.begin(), folder.end());
        std::vector<std::string> result;
        result.push_back(folder[0]);
        for (int i = 1; i < folder.size(); ++i) {
            auto last = result.back();
            last.push_back('/');
            if (folder[i].substr(0, last.size()) == last)
                continue;

            result.push_back(folder[i]);
        }
        return result;
    }
};