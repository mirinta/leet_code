#include <map>
#include <stack>
#include <string>

/**
 * Given a string formula representing a chemical formula, return the count of each atom.
 *
 * The atomic element always starts with an uppercase character, then zero or more lowercase
 * letters, representing the name.
 *
 * One or more digits representing that element's count may follow if the count is greater than 1.
 * If the count is 1, no digits will follow.
 *
 * - For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.
 *
 * Two formulas are concatenated together to produce another formula.
 *
 * - For example, "H2O2He3Mg4" is also a formula.
 *
 * A formula placed in parentheses, and a count (optionally added) is also a formula.
 *
 * - For example, "(H2O2)" and "(H2O2)3" are formulas.
 *
 * Return the count of all elements as a string in the following form: the first name (in sorted
 * order), followed by its count (if that count is more than 1), followed by the second name (in
 * sorted order), followed by its count (if that count is more than 1), and so on.
 *
 * The test cases are generated so that all the values in the output fit in a 32-bit integer.
 *
 * ! 1 <= formula.length <= 1000
 * ! formula consists of English letters, digits, '(', and ')'.
 * ! formula is always valid.
 */

class Solution {
public:
    std::string countOfAtoms(std::string formula)
    {
        const int n = formula.size();
        std::map<std::string, int> map;
        std::stack<std::map<std::string, int>> stack;
        int i = 0;
        while (i < n) {
            if (formula[i] == '(') {
                stack.push(map);
                map.clear();
                i++;
            } else if (formula[i] == ')') {
                int j = i + 1;
                int num = 0;
                while (j < n && std::isdigit(formula[j])) {
                    num = num * 10 + (formula[j] - '0');
                    j++;
                }
                num = std::max(1, num);
                for (const auto& [element, count] : map) {
                    stack.top()[element] += count * num;
                }
                map = stack.top();
                stack.pop();
                i = j;
            } else if (std::isupper(formula[i])) {
                int j = i + 1;
                while (j < n && std::islower(formula[j])) {
                    j++;
                }
                const auto element = formula.substr(i, j - i);
                int num = 0;
                while (j < n && std::isdigit(formula[j])) {
                    num = num * 10 + (formula[j] - '0');
                    j++;
                }
                map[element] += std::max(1, num);
                i = j;
            }
        }
        std::string result;
        for (const auto& [element, count] : map) {
            result.append(element);
            if (count > 1) {
                result.append(std::to_string(count));
            }
        }
        return result;
    }
};