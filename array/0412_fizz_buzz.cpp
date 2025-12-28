#include <string>
#include <vector>

/**
 * Given an integer "n", return a string array "answer" (1-indexed) where:
 *
 * - answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
 *
 * - answer[i] == "Fizz" if i is divisible by 3.
 *
 * - answer[i] == "Buzz" if i is divisible by 5.
 *
 * - answer[i] == "i" (as a string) if none of the above conditions are true
 */

class Solution {
public:
    std::vector<std::string> fizzBuzz(int n)
    {
        if (n <= 0)
            return {};

        const std::string buzz{"Buzz"};
        const std::string fizz{"Fizz"};
        const std::string fizzbuzz = fizz + buzz;
        std::vector<std::string> result(n, "");
        for (size_t i = 0; i < result.size(); ++i) {
            const auto num = i + 1;
            if (num % 15 == 0) {
                result[i] = fizzbuzz;
            } else if (num % 3 == 0) {
                result[i] = fizz;
            } else if (num % 5 == 0) {
                result[i] = buzz;
            } else {
                result[i] = std::to_string(num);
            }
        }
        return result;
    }
};