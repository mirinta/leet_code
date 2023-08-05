#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * A transformation sequence from word beginWord to word endWord using a dictionary wordList is a
 * sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
 *
 * - Every adjacent pair of words differs by a single letter.
 *
 * - Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
 *
 * - sk == endWord
 *
 * Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in
 * the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
 *
 * ! 1 <= beginWord.length <= 10
 * ! endWord.length == beginWord.length
 * ! 1 <= wordList.length <= 5000
 * ! wordList[i].length == beginWord.length
 * ! beginWord, endWord, and wordList[i] consist of lowercase English letters.
 * ! beginWord != endWord
 * ! All the words in wordList are unique.
 */

class Solution
{
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList)
    {
        std::unordered_set<std::string> validWords(wordList.begin(), wordList.end());
        if (!validWords.count(endWord))
            return 0;

        std::unordered_set<std::string> visited;
        visited.insert(beginWord);
        std::queue<std::string> queue;
        queue.push(beginWord);
        int result = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto word = queue.front();
                queue.pop();
                if (word == endWord)
                    return result + 1;

                for (int i = 0; i < word.size(); ++i) {
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == word[i])
                            continue;

                        std::string transform = word;
                        transform[i] = c;
                        if (visited.count(transform) || !validWords.count(transform))
                            continue;

                        visited.insert(transform);
                        queue.push(std::move(transform));
                    }
                }
            }
            result++;
        }
        return 0;
    }
};