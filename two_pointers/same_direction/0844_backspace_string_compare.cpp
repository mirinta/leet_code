#include <stack>
#include <string>

/**
 * Given two strings s and t, return true if they are equal when both are typed into empty text
 * editors. '#' means a backspace character.
 *
 * Note that after backspacing an empty text, the text will continue empty.
 *
 * ! 1 <= s.length, t.length <= 200
 * ! s and t only contain lowercase letters and '#' characters.
 */

class Solution {
public:
    bool backspaceCompare(std::string s, std::string t)
    {
        return approach2(s, t);
    }

private:
    bool approach2(const std::string& s, const std::string& t)
    {
        int i = s.size() - 1;
        int j = t.size() - 1;
        int removeS = 0;
        int removeT = 0;
        while (i >= 0 || j >= 0) {
            while (i >= 0) {
                if (std::isalpha(s[i]) && removeS == 0)
                    break;

                if (s[i] == '#') {
                    removeS++;
                } else {
                    removeS--;
                }
                i--;
            }
            while (j >= 0) {
                if (std::isalpha(t[j]) && removeT == 0)
                    break;

                if (t[j] == '#') {
                    removeT++;
                } else {
                    removeT--;
                }
                j--;
            }
            if ((i < 0 && j >= 0) || (i >= 0 && j < 0))
                return false;

            if (i >= 0 && j >= 0 && s[i] != t[j])
                return false;

            i--;
            j--;
        }
        return true;
    }

    bool approach1(const std::string& s, const std::string& t)
    {
        return process(s) == process(t);
    }

    std::string process(const std::string& s)
    {
        std::string result;
        for (const auto& c : s) {
            if (c == '#' && !result.empty()) {
                result.pop_back();
            } else if (std::isalpha(c)) {
                result.push_back(c);
            }
        }
        return result;
    }
};