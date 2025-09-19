#include <array>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a wordlist, we want to implement a spellchecker that converts a query word into a correct
 * word.
 *
 * For a given query word, the spell checker handles two categories of spelling mistakes:
 *
 * - Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query
 * word is returned with the same case as the case in the wordlist.
 *
 *   - Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
 *
 *   - Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
 *
 *   - Example: wordlist = ["yellow"], query = "yellow": correct = "yellow"
 *
 * - Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u') of the query word with
 * any vowel individually, it matches a word in the wordlist (case-insensitive), then the query word
 * is returned with the same case as the match in the wordlist.
 *
 *   - Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
 *
 *   - Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no match)
 *
 *   - Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no match)
 *
 * In addition, the spell checker operates under the following precedence rules:
 *
 * - When the query exactly matches a word in the wordlist (case-sensitive), you should return the
 * same word back.
 *
 * - When the query matches a word up to capitalization, you should return the first such match in
 * the wordlist.
 *
 * - When the query matches a word up to vowel errors, you should return the first such match in the
 * wordlist.
 *
 * - If the query has no matches in the wordlist, you should return the empty string.
 *
 * Given some queries, return a list of words answer, where answer[i] is the correct word for query
 * = queries[i].
 *
 * ! 1 <= wordlist.length, queries.length <= 5000
 * ! 1 <= wordlist[i].length, queries[i].length <= 7
 * ! wordlist[i] and queries[i] consist only of only English letters.
 */

class Solution
{
public:
    std::vector<std::string> spellchecker(std::vector<std::string>& wordlist,
                                          std::vector<std::string>& queries)
    {
        std::array<std::unordered_map<std::string, int>, 3> maps;
        for (int i = 0; i < wordlist.size(); ++i) {
            const auto& origin = wordlist[i];
            if (!maps[0].count(origin)) {
                maps[0][origin] = i;
            }
            if (const auto s = helper1(origin); !maps[1].count(s)) {
                maps[1][s] = i;
            }
            if (const auto s = helper2(origin); !maps[2].count(s)) {
                maps[2][s] = i;
            }
        }
        std::vector<std::string> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            if (maps[0].count(q)) {
                result.push_back(wordlist[maps[0][q]]);
            } else if (const auto s = helper1(q); maps[1].count(s)) {
                result.push_back(wordlist[maps[1][s]]);
            } else if (const auto s = helper2(q); maps[2].count(s)) {
                result.push_back(wordlist[maps[2][s]]);
            } else {
                result.emplace_back();
            }
        }
        return result;
    }

private:
    std::string helper1(const std::string& s)
    {
        std::string result = s;
        for (auto& c : result) {
            c = std::tolower(c);
        }
        return result;
    }

    std::string helper2(const std::string& s)
    {
        std::string result = s;
        for (auto& c : result) {
            c = std::tolower(c);
            c = isVowel(c) ? '#' : c;
        }
        return result;
    }

    bool isVowel(char c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }
};