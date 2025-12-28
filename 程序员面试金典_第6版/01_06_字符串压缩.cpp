#include <string>

/**
 * 字符串压缩。利用字符重复出现的次数，编写一种方法，实现基本的字符串压缩功能。比如，字符串aabcccccaaa会变为a2b1c5a3。若“压缩”后的字符串没有变短，则返回原先的字符串。你可以假设字符串中只包含大小写英文字母（a至z）。
 *
 * ! 字符串长度在[0, 50000]范围内。
 */

class Solution {
public:
    std::string compressString(std::string S)
    {
        const int n = S.size();
        int i = 0;
        std::string result;
        while (i < n) {
            int j = i + 1;
            int count = 1;
            while (j < n && S[j] == S[j - 1]) {
                j++;
                count++;
            }
            result.push_back(S[i]);
            result.append(std::to_string(count));
            if (result.size() >= n)
                return S;

            i = j;
        }
        return result;
    }
};