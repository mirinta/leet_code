#include <map>
#include <string>
#include <vector>

/**
 * Design a data structure that simulates an in-memory file system.
 *
 * Implement the FileSystem class:
 *
 * - FileSystem() Initializes the object of the system.
 *
 * - List<String> ls(String path)
 *
 *   - If path is a file path, returns a list that only contains this file's name.
 *
 *   - If path is a directory path, returns the list of file and directory names in this directory.
 *
 *   - The answer should in lexicographic order.
 *
 * - void mkdir(String path) Makes a new directory according to the given path. The given directory
 * path does not exist. If the middle directories in the path do not exist, you should create them
 * as well.
 *
 * - void addContentToFile(String filePath, String content)
 *
 *   - If filePath does not exist, creates that file containing given content.
 *
 *   - If filePath already exists, appends the given content to original content.
 *
 * - String readContentFromFile(String filePath) Returns the content in the file at filePath.
 *
 * ! 1 <= path.length, filePath.length <= 100
 *
 * ! path and filePath are absolute paths which begin with '/' and do not end with '/' except that
 * ! the path is just "/".
 *
 * ! You can assume that all directory names and file names only contain lowercase letters, and the
 * ! same names will not exist in the same directory.
 *
 * ! You can assume that all operations will be passed valid parameters, and users will not attempt
 * ! to retrieve file content or list a directory or file that does not exist.
 *
 * ! 1 <= content.length <= 50
 *
 * ! At most 300 calls will be made to ls, mkdir, addContentToFile, and readContentFromFile.
 */

struct TrieNode {
    bool isFile{false};
    std::string content; // if it is not a file, content must be empty
    std::map<std::string, TrieNode*> next;
};

class FileSystem {
public:
    FileSystem() : root(new TrieNode) {}

    std::vector<std::string> ls(std::string path)
    {
        const auto names = split(path);
        auto* node = root;
        for (const auto& name : names) {
            if (!node->next.count(name))
                return {};

            node = node->next[name];
        }
        if (node->isFile)
            return {names.back()};

        std::vector<std::string> result(node->next.size());
        for (int i = 0; i < result.size(); ++i) {
            result[i] = std::next(node->next.begin(), i)->first;
        }
        return result;
    }

    void mkdir(std::string path)
    {
        const auto names = split(path);
        auto* node = root;
        for (const auto& name : names) {
            if (!node->next.count(name)) {
                node->next[name] = new TrieNode();
            }
            node = node->next[name];
        }
    }

    void addContentToFile(std::string filePath, std::string content)
    {
        const auto names = split(filePath);
        auto* node = root;
        for (const auto& name : names) {
            if (!node->next.count(name)) {
                node->next[name] = new TrieNode();
            }
            node = node->next[name];
        }
        node->isFile = true;
        node->content.append(content);
    }

    std::string readContentFromFile(std::string filePath)
    {
        const auto names = split(filePath);
        auto* node = root;
        for (const auto& name : names) {
            if (!node->next.count(name))
                return {};

            node = node->next[name];
        }
        return node->content;
    }

private:
    std::vector<std::string> split(const std::string& path)
    {
        const int n = path.size();
        std::vector<std::string> result{""}; // assume path[0] = '/'
        int i = 1;
        while (i < n) {
            int j = i;
            while (j < n && path[j] != '/') {
                j++;
            }
            result.push_back(path.substr(i, j - i));
            i = j + 1;
        }
        return result;
    }

private:
    TrieNode* root;
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */