#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence
 * where each word is a valid dictionary word. Return all such possible sentences in any order.
 *
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 *
 * ! 1 <= s.length <= 20
 * ! 1 <= wordDict.length <= 1000
 * ! 1 <= wordDict[i].length <= 10
 * ! s and wordDict[i] consist of only lowercase English letters.
 * ! All the strings of wordDict are unique.
 * ! Input is generated in a way that the length of the answer doesn't exceed 105.
 */

class Solution {
public:
    std::vector<std::string> wordBreak(std::string s, std::vector<std::string>& wordDict)
    {
        std::unordered_set<std::string> set(wordDict.begin(), wordDict.end());
        std::vector<std::string> path;
        std::vector<std::string> result;
        backtrack(result, path, 0, s, set);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result,
                   std::vector<std::string>& path,
                   int i,
                   const std::string& s,
                   const std::unordered_set<std::string>& set)
    {
        if (i == s.size()) {
            std::string concat;
            for (const auto& word : path) {
                concat.append(word);
                concat.push_back(' ');
            }
            concat.pop_back();
            result.push_back(std::move(concat));
            return;
        }
        for (int j = i; j < s.size(); ++j) {
            auto word = s.substr(i, j - i + 1);
            if (!set.count(word))
                continue;

            path.push_back(std::move(word));
            backtrack(result, path, j + 1, s, set);
            path.pop_back();
        }
    }
};