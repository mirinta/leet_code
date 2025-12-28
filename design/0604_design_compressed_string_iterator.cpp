#include <string>

/**
 * Design and implement a data structure for a compressed string iterator. The given compressed
 * string will be in the form of each letter followed by a positive integer representing the number
 * of this letter existing in the original uncompressed string.
 *
 * Implement the StringIterator class:
 *
 * - next() Returns the next character if the original string still has uncompressed characters,
 * otherwise returns a white space.
 *
 * - hasNext() Returns true if there is any letter needs to be uncompressed in the original string,
 * otherwise returns false.
 *
 * ! 1 <= compressedString.length <= 1000
 * ! compressedString consists of lower-case an upper-case English letters and digits.
 * ! The number of a single character repetitions in compressedString is in the range [1, 10^9]
 * ! At most 100 calls will be made to next and hasNext.
 */

class StringIterator {
public:
    StringIterator(std::string compressedString) : s(std::move(compressedString)) {}

    char next()
    {
        if (!hasNext())
            return ' ';

        if (count == 0) {
            c = s[i++];
            while (i < s.size() && std::isdigit(s[i])) {
                count = count * 10 + (s[i] - '0');
                i++;
            }
        }
        count--;
        return c;
    }

    bool hasNext()
    {
        return i < s.size() || count > 0;
    }

private:
    int i{0};
    int count{0};
    char c{' '};
    std::string s;
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */