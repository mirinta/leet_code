#include <string>
#include <vector>

/**
 * 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。
 *
 * 例如输入字符串"I am a student. "，则输出"student. a am I"。
 *
 * ! 无空格字符构成一个单词。
 * ! 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
 * ! 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
 *
 * ! 本题与LC 151相同。
 */

class Solution {
public:
    std::string reverseWords(std::string s)
    {
        std::vector<std::string> words;
        int left = 0;
        int right = 0;
        while (left < s.size()) {
            while (left < s.size() && s[left] == ' ') {
                left++;
            }
            right = left;
            while (right < s.size() && s[right] != ' ') {
                right++;
            }
            if (right > left) {
                words.push_back(s.substr(left, right - left));
            }
            left = right;
        }
        std::reverse(words.begin(), words.end());
        std::string result;
        for (int i = 0; i < words.size(); ++i) {
            result.append(words[i]);
            if (i != words.size() - 1) {
                result.push_back(' ');
            }
        }
        return result;
    }
};