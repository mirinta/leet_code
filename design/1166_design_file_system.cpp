#include <string>
#include <unordered_map>

/**
 * You are asked to design a file system that allows you to create new paths and associate them with
 * different values.
 *
 * The format of a path is one or more concatenated strings of the form: / followed by one or more
 * lowercase English letters. For example, "/leetcode" and "/leetcode/problems" are valid paths
 * while an empty string "" and "/" are not.
 *
 * Implement the FileSystem class:
 *
 * - bool createPath(string path, int value) Creates a new path and associates a value to it if
 * possible and returns true. Returns false if the path already exists or its parent path doesn't
 * exist.
 *
 * - int get(string path) Returns the value associated with path or returns -1 if the path doesn't
 * exist.
 *
 * ! 2 <= path.length <= 100
 * ! 1 <= value <= 10^9
 * ! Each path is valid and consists of lowercase English letters and '/'.
 * ! At most 10^4 calls in total will be made to createPath and get.
 */

class FileSystem {
public:
    FileSystem() {}

    bool createPath(std::string path, int value)
    {
        if (path.empty() || path == "/")
            return false;

        if (map.count(path))
            return false;

        auto parent = path.substr(0, path.find_last_of('/'));
        if (!parent.empty() && !map.count(parent))
            return false;

        map[path] = value;
        return true;
    }

    int get(std::string path)
    {
        if (!map.count(path))
            return -1;

        return map[path];
    }

private:
    std::unordered_map<std::string, int> map;
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */