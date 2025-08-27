#include <set>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a list of phrases, generate a list of Before and After puzzles.
 *
 * A phrase is a string that consists of lowercase English letters and spaces only. No space appears
 * in the start or the end of a phrase. There are no consecutive spaces in a phrase.
 *
 * Before and After puzzles are phrases that are formed by merging two phrases where the last word
 * of the first phrase is the same as the first word of the second phrase.
 *
 * Return the Before and After puzzles that can be formed by every two phrases phrases[i] and
 * phrases[j] where i != j. Note that the order of matching two phrases matters, we want to consider
 * both orders.
 *
 * You should return a list of distinct strings sorted lexicographically.
 *
 * ! 1 <= phrases.length <= 100
 * ! 1 <= phrases[i].length <= 100
 */

class Solution
{
public:
    std::vector<std::string> beforeAndAfterPuzzles(std::vector<std::string>& phrases)
    {
        const int n = phrases.size();
        std::unordered_map<std::string, std::vector<int>> head;
        std::unordered_map<std::string, std::vector<int>> tail;
        for (int i = 0; i < n; ++i) {
            head[getFirstWord(phrases[i])].push_back(i);
            tail[getLastWord(phrases[i])].push_back(i);
        }
        std::set<std::string> set;
        for (const auto& [s, indices] : tail) {
            if (!head.count(s))
                continue;

            for (const auto& i : indices) {
                for (const auto& j : head[s]) {
                    if (i == j)
                        continue;

                    set.insert(concat(phrases[i], phrases[j], s.size()));
                }
            }
        }
        return {set.begin(), set.end()};
    }

private:
    std::string concat(const std::string& s1, const std::string& s2, int len)
    {
        return s1.substr(0, s1.size() - len) + s2;
    }

    std::string getFirstWord(const std::string& s)
    {
        auto pos = s.find_first_of(' ');
        if (pos == std::string::npos)
            return s;

        return s.substr(0, pos);
    }

    std::string getLastWord(const std::string& s)
    {
        auto pos = s.find_last_of(' ');
        if (pos == std::string::npos)
            return s;

        return s.substr(pos + 1);
    }
};