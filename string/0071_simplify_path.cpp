#include <sstream>
#include <string>
#include <vector>

/**
 * Given a string path, which is an absolute path (starting with a slash '/') to a file or directory
 * in a Unix-style file system, convert it to the simplified canonical path.
 *
 * In a Unix-style file system, a period '.' refers to the current directory, a double period '..'
 * refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated
 * as a single slash '/'. For this problem, any other format of periods such as '...' are treated as
 * file/directory names.
 *
 * The canonical path should have the following format:
 *
 * - The path starts with a single slash '/'.
 *
 * - Any two directories are separated by a single slash '/'.
 *
 * - The path does not end with a trailing '/'.
 *
 * - The path only contains the directories on the path from the root directory to the target file
 * or directory (i.e., no period '.' or double period '..')
 *
 * Return the simplified canonical path.
 *
 * ! 1 <= path.length <= 3000
 * ! path consists of English letters, digits, period '.', slash '/' or '_'.
 * ! path is a valid absolute Unix path.
 */

class Solution {
public:
    std::string simplifyPath(std::string path)
    {
        std::istringstream stream(path);
        std::string s;
        std::vector<std::string> split;
        while (std::getline(stream, s, '/')) {
            if (s.empty() || s == ".")
                continue;

            if (s == "..") {
                if (!split.empty()) {
                    split.pop_back();
                }
                continue;
            }
            split.push_back(s);
        }
        std::string result{"/"};
        for (int i = 0; i < split.size(); ++i) {
            result.append(split[i]);
            if (i != split.size() - 1) {
                result.push_back('/');
            }
        }
        return result;
    }
};
