#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths,
 * where paths[i] is an array representing an absolute path to the ith folder in the file system.
 *
 * - For example, ["one", "two", "three"] represents the path "/one/two/three".
 *
 * Two folders (not necessarily on the same level) are identical if they contain the same non-empty
 * set of identical subfolders and underlying subfolder structure. The folders do not need to be at
 * the root level to be identical. If two or more folders are identical, then mark the folders as
 * well as all their subfolders.
 *
 * - For example, folders "/a" and "/b" in the file structure below are identical. They (as well as
 * their subfolders) should all be marked:
 *   - /a
 *   - /a/x
 *   - /a/x/y
 *   - /a/z
 *   - /b
 *   - /b/x
 *   - /b/x/y
 *   - /b/z
 *
 * - However, if the file structure also included the path "/b/w", then the folders "/a" and "/b"
 * would not be identical. Note that "/a/x" and "/b/x" would still be considered identical even with
 * the added folder.
 *
 * Once all the identical folders and their subfolders have been marked, the file system will delete
 * all of them. The file system only runs the deletion once, so any folders that become identical
 * after the initial deletion are not deleted.
 *
 * Return the 2D array ans containing the paths of the remaining folders after deleting all the
 * marked folders. The paths may be returned in any order.
 *
 * ! 1 <= paths.length <= 2 * 10^4
 * ! 1 <= paths[i].length <= 500
 * ! 1 <= paths[i][j].length <= 10
 * ! 1 <= sum(paths[i][j].length) <= 2 * 10^5
 * ! path[i][j] consists of lowercase English letters.
 * ! No two paths lead to the same folder.
 * ! For any folder not at the root level, its parent folder will also be in the input.
 */

class Solution {
public:
    std::vector<std::vector<std::string>> deleteDuplicateFolder(std::vector<std::vector<std::string>>& paths)
    {
        auto* root = new TrieNode;
        for (const auto& path : paths) {
            auto* node = root;
            for (const auto& s : path) {
                if (!node->next.count(s)) {
                    node->next[s] = new TrieNode;
                }
                node = node->next[s];
            }
        }
        std::unordered_map<std::string, int> map; // <code, count>
        std::function<void(TrieNode*)> build = [&](TrieNode* node) {
            if (!node || node->next.empty())
                return;

            std::vector<std::string> v;
            for (const auto& [subfolder, child] : node->next) {
                build(child);
                v.push_back(subfolder + '(' + child->code + ')');
            }
            std::sort(v.begin(), v.end());
            for (auto& s : v) {
                node->code += std::move(s);
            }
            map[node->code]++;
        };
        build(root);
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> path;
        std::function<void(TrieNode*)> backtrack = [&](TrieNode* node) {
            if (!node || map[node->code] > 1)
                return;

            if (!path.empty()) {
                result.push_back(path);
            }
            for (const auto& [subfolder, child] : node->next) {
                path.push_back(subfolder);
                backtrack(child);
                path.pop_back();
            }
        };
        backtrack(root);
        return result;
    }

private:
    struct TrieNode {
        std::string code;
        std::unordered_map<std::string, TrieNode*> next;
    };
};