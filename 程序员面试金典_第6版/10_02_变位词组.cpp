#include <algorithm>
#include <string>
#include <unordered_map>

/**
 * 编写一种方法，对字符串数组进行排序，将所有变位词组合在一起。变位词是指字母相同，但排列不同的字符串。
 *
 * 注意：本题相对原题稍作修改
 *
 * ! 所有输入均为小写字母。
 * ! 不考虑答案输出的顺序。
 */

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& s : strs) {
            auto key = s;
            std::sort(key.begin(), key.end());
            map[key].push_back(s);
        }
        std::vector<std::vector<std::string>> result;
        for (const auto& [key, anagrams] : map) {
            result.push_back(anagrams);
        }
        return result;
    }
};